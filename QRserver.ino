
#include <FS.h>
#include <LittleFS.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>


const char *ssid = "Ō";
const char *password = "987654321";
int M;

          AsyncWebServer server(80);

IPAddress local_IP(192,168,4,20);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);
void setup()
{

          if(!LittleFS.begin()){
            Serial.println("An Error is had to have occured while mounting LittleFS");
            return;
          }
            Serial.printf("LocalsIP: %d\n", WiFi.localIP());
            
            server.on("/", HTTP_GET, [](AsyncWebServerRequest *request) {
              request->send(LittleFS, "/index.html", String(), false);
            });
            server.on("/QR.png", HTTP_GET, [](AsyncWebServerRequest *request) {
              request->send(LittleFS, "/QR.png" );
            });



  
  Serial.begin(115200);
  Serial.println();
  Serial.print("Setting soft-AP configuration ... ");
  Serial.println(WiFi.softAPConfig(local_IP, gateway, subnet) ? "Ready1" : "Failed!");
  Serial.print("Setting soft-AP ... ");
  Serial.println(WiFi.softAP(ssid,password) ? "Ready2" : "Failed!");
  //WiFi.softAP(ssid);
  //WiFi.softAP(ssid, password, channel, hidden, max_connection)
  
  Serial.print("Soft-AP IP address = ");
  Serial.println(WiFi.softAPIP());
            server.begin();
 }
void loop() {
  Serial.print("[Server Connected]: ");
  Serial.println(WiFi.softAPIP());
  Serial.printf("Stations connected to soft-AP = %d\n", WiFi.softAPgetStationNum());
  if (   WiFi.softAPgetStationNum() > M) 
      { Serial.print("[Added] ");
      M =  WiFi.softAPgetStationNum();}

  Serial.printf("M = %d\n", M);
  
  delay(500);
}
