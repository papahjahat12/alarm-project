#include <ESP8266WiFi.h>
#include <UniversalTelegramBot.h>
#include <WiFiClientSecure.h>
#include <ArduinoJson.h>

// Kredensial Jaringan
const char* ssid = "Redmi";
const char* password = "12345678";

// Inisialisasi Telegram BOT
#define BOTtoken "6445761320:AAG1kmO5hJiwBIw2yzJ8K1qX7PNnBy_csgI"  

// Message you
#define CHAT_ID "6263017356"

// Define pins
const int buttonPins[8] = {D1, D2, D3, D4, D5, D6, D7, D8};
const int relayPin = D0;    // Pin connected to Relay

// Variabel untuk menyimpan status tombol
int buttonState = LOW;

WiFiClientSecure client;
UniversalTelegramBot bot(BOTtoken, client);

void setup() {
  // Inisialisasi pin tombol sebagai input dengan pull-down resistor
  for (int i = 0; i < 8; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);  // Menggunakan pull-down resistor internal
  }
  pinMode(relayPin, OUTPUT);  // Inisialisasi pin relay sebagai output
  digitalWrite(relayPin, LOW);  // Pastikan relay mati pada awalnya
  Serial.begin(115200);  // Untuk debugging

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Telegram
  client.setInsecure();
}

void loop() {
  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {
      digitalWrite(relayPin, LOW);  // Tombol di tekan alarm mati
      Serial.println("Alarm Mati!!");  // Untuk debugging

    } else if (digitalRead(buttonPins[i]) == HIGH) {
      digitalWrite(relayPin, HIGH);
      Serial.println("Alarm Menyala");
      delay(1000);  // Debounce, dan berikan waktu untuk alarm aktif
      digitalWrite(relayPin, LOW);  // Matikan relay setelah jeda waktu
    
    // Send notification to Telegram
    String message = "Alarm activated! Button pressed.";
    bot.sendMessage(CHAT_ID, "HANDPHONE TERLEPAS", "");

    // Add a small delay to debounce the button
    delay(5);

    // Menambahkan sedikit jeda untuk stabilitas
    delay(5);
  
    }
}
