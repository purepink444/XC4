#include <AsyncTCP.h>
#include <WiFi.h>
#include <ESPAsyncWebServer.h>

// กำหนดชื่อ WiFi และรหัสผ่าน
const char* ssid = "LIKAE-IoT";  
const char* password = "Rbbrb29199218";  

// กำหนดพอร์ตของรีเลย์
int R1 = 23;
int R2 = 22;
int R3 = 21;
int R4 = 19;

// สร้าง WebServer
AsyncWebServer server(80);

// ฟังก์ชันเพื่อสร้างหน้าเว็บพร้อมข้อมูลสถานะปัจจุบันของรีเลย์
String getRelayStatus() {
  String status = "<html><body><h1>Control Relays</h1>";
  status += "<p>Relay 1 is " + String(digitalRead(R1) == HIGH ? "ON" : "OFF") + "</p>";
  status += "<p>Relay 2 is " + String(digitalRead(R2) == HIGH ? "ON" : "OFF") + "</p>";
  status += "<p>Relay 3 is " + String(digitalRead(R3) == HIGH ? "ON" : "OFF") + "</p>";
  status += "<p>Relay 4 is " + String(digitalRead(R4) == HIGH ? "ON" : "OFF") + "</p>";
  status += "<p><a href=\"/relay1/toggle\"><button>Toggle Relay 1</button></a></p>";
  status += "<p><a href=\"/relay2/toggle\"><button>Toggle Relay 2</button></a></p>";
  status += "<p><a href=\"/relay3/toggle\"><button>Toggle Relay 3</button></a></p>";
  status += "<p><a href=\"/relay4/toggle\"><button>Toggle Relay 4</button></a></p>";
  status += "</body></html>";
  return status;
}

void setup() {
  // เริ่มต้น Serial communication
  Serial.begin(115200);

  // ตั้งค่าพอร์ต
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  pinMode(R3, OUTPUT);
  pinMode(R4, OUTPUT);

  // เชื่อมต่อกับ WiFi
  WiFi.begin(ssid, password);
  Serial.println("Connecting to WiFi...");

  // รอจนกว่าเชื่อมต่อได้
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting...");
  }

  // เมื่อเชื่อมต่อได้แล้ว
  Serial.println("Connected to WiFi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());  // แสดง IP ของ ESP32

  // กำหนดหน้าเว็บที่ใช้ควบคุมรีเลย์
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    // ส่งข้อมูลสถานะปัจจุบันของรีเลย์
    request->send(200, "text/html", getRelayStatus());
  });

  // สร้างการควบคุม Relay ผ่าน URL (Toggle)
  server.on("/relay1/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    // ตรวจสอบสถานะของ Relay 1 และสลับสถานะ
    if (digitalRead(R1) == HIGH) {
      digitalWrite(R1, LOW);  // ปิด
    } else {
      digitalWrite(R1, HIGH); // เปิด
    }
    request->send(200, "text/html", getRelayStatus());
  });

  server.on("/relay2/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    // ตรวจสอบสถานะของ Relay 2 และสลับสถานะ
    if (digitalRead(R2) == HIGH) {
      digitalWrite(R2, LOW);  // ปิด
    } else {
      digitalWrite(R2, HIGH); // เปิด
    }
    request->send(200, "text/html", getRelayStatus());
  });

  server.on("/relay3/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    // ตรวจสอบสถานะของ Relay 3 และสลับสถานะ
    if (digitalRead(R3) == HIGH) {
      digitalWrite(R3, LOW);  // ปิด
    } else {
      digitalWrite(R3, HIGH); // เปิด
    }
    request->send(200, "text/html", getRelayStatus());
  });

  server.on("/relay4/toggle", HTTP_GET, [](AsyncWebServerRequest *request){
    // ตรวจสอบสถานะของ Relay 4 และสลับสถานะ
    if (digitalRead(R4) == HIGH) {
      digitalWrite(R4, LOW);  // ปิด
    } else {
      digitalWrite(R4, HIGH); // เปิด
    }
    request->send(200, "text/html", getRelayStatus());
  });

  // เริ่ม server
  server.begin();
}

void loop() {
  // ไม่มีการทำงานใน loop เนื่องจาก server ทำงานใน background
}
