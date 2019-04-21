/*
   Copyright (c) 2015, Majenko Technologies
   All rights reserved.

   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:

 * * Redistributions of source code must retain the above copyright notice, this
     list of conditions and the following disclaimer.

 * * Redistributions in binary form must reproduce the above copyright notice, this
     list of conditions and the following disclaimer in the documentation and/or
     other materials provided with the distribution.

 * * Neither the name of Majenko Technologies nor the names of its
     contributors may be used to endorse or promote products derived from
     this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
   ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
   WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
   DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
   ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
   ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/* Create a WiFi access point and provide a web server on it. */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

void writeString(char add,String data);
String read_String(char add);

#ifndef APSSID
#define APSSID "PaulESP"
#define APPSK  "paulsin91@"
#endif

/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;

ESP8266WebServer server(80);

int i = 749, j = 255, k = 378;
int AnalogReadValue = 0;

int LED_NUMBER = 16; 
int D4 = 4; 
int D12 = 12;
int D13 = 13;
int D14 = 14;
int D16 = 16;

//LED_BUILTIN - D2- ESP17
// D4  - ESP19
// D16 - ESP4
// D14 - ESP5
// D12 - ESP6
// D13 - ESP7   

/* Just a little test message.  Go to http://192.168.4.1 in a web browser
   connected to this access point to see it.
*/
void handleRoot() {
  server.send(200, "text/plain", String(k));
}

void OnLED1() {
  digitalWrite(D4, LOW); 
}
void OffLED1() {
  digitalWrite(D4, HIGH);
}

void OnLED2() {
  digitalWrite(D12, LOW); 
}
void OffLED2() {
  digitalWrite(D12, HIGH);
}

void OnLED3() {
  digitalWrite(D13, LOW); 
}
void OffLED3() {
  digitalWrite(D13, HIGH);
}

void OnLED4() {
  digitalWrite(D14, LOW); 
}
void OffLED4() {
  digitalWrite(D14, HIGH);
}

void OnLED5() {
  digitalWrite(D16, LOW); 
}
void OffLED5() {
  digitalWrite(D16, HIGH);
}

void AnalogRead() {
  server.send(200, "text/plain", String(AnalogReadValue));
}

void setup() {
  delay(1000);
  Serial.begin(115200);
  Serial.println();
  Serial.print("Configuring access point...");
  /* You can remove the password parameter if you want the AP to be open. */
  WiFi.mode(WIFI_AP);
  WiFi.softAP(ssid, password);

  IPAddress myIP = WiFi.softAPIP();
  Serial.print("AP IP address: ");
  Serial.println(myIP);
  
  pinMode(D4, OUTPUT);
  pinMode(D12, OUTPUT);
  pinMode(D13, OUTPUT);
  pinMode(D14, OUTPUT);
  pinMode(D16, OUTPUT);

  digitalWrite(D4, HIGH);
  digitalWrite(D12, HIGH);
  digitalWrite(D13, HIGH);
  digitalWrite(D14, HIGH);
  digitalWrite(D16, HIGH);
    
  server.on("/", handleRoot);
  
  server.on("/OnLED1", OnLED1);
  server.on("/OffLED1", OffLED1);

  server.on("/OnLED2", OnLED2);
  server.on("/OffLED2", OffLED2);

  server.on("/OnLED3", OnLED3);
  server.on("/OffLED3", OffLED3);
  
  server.on("/OnLED4", OnLED4);
  server.on("/OffLED4", OffLED4);

  server.on("/OnLED5", OnLED5);
  server.on("/OffLED5", OffLED5);
  
  server.on("/AnalogRead", AnalogRead);
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
  AnalogReadValue++;
  if(AnalogReadValue>=1000) {
    AnalogReadValue = 0;
  }
}
