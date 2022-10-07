#include <AFMotor.h> //library for adafruit motor shield
#include <Servo.h>  //servo library

AF_DCMotor motor1(1); //motor1 (left)
AF_DCMotor motor2(2); //motor2 (right)

Servo steering;       //steering servo 
Servo servo1;         //left back wheel servo
Servo servo2;         //right back wheel servo

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  
  servo1.attach(9);
  servo2.attach(10);
  steering.attach(11);

}

void loop() {
  // put your main code here, to run repeatedly:
  String cmd;
  if(Serial.available()){
    cmd = Serial.readStringUntil('\n'); // Recebe Comando
    Serial.println(cmd); // DEBUG
    int Speed = 0, rot = 0; // Variáveis para armazenar a velocidade e rotação do rover
    if(cmd.indexOf("S") != -1 && cmd.indexOf("R") != -1 && (cmd.indexOf("Car") != -1 || cmd.indexOf("Boat") != -1)){
      Speed = cmd.substring(cmd.indexOf("S") + 1).toInt();// Obtém a velocidade enviada
      rot = cmd.substring(cmd.indexOf("R") + 1).toInt(); // Obtém a rotação enviada
      // Coloca o rover no modo desejado
      if(cmd.indexOf("Car") != -1){
        carMode(Speed,rot);
      }
      else if(cmd.indexOf("Boat") != -1){
        boatMode(Speed,rot);
      }      
    }
  }
}

//boat mode function
void boatMode(int boatSpeed, int rot){
  servo1.write(90);
  servo2.write(90);


  //Seleciona o sentido de rotação dos motores
  if(boatSpeed > 0){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if(boatSpeed < 0){
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
  }
  else{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }
  
  boatSpeed = abs(boatSpeed);
  boatSpeed = constrain(boatSpeed, 0, 255);
  rot = constrain(rot, 60, 120);
    
  motor1.setSpeed(boatSpeed);
  motor2.setSpeed(boatSpeed);
  Serial.println("Modo Barco ativo com Velocidade: " + String(boatSpeed) + " e Rotação: " + String(rot)); // DEBUG
    
  servo1.write(rot);
  servo2.write(180-rot);
  
}

//car  mode function
void carMode(int Carspeed,int rot){
  servo1.write(0);
  servo2.write(180);

  //Seleciona o sentido de rotação dos motores
  if(Carspeed > 0){
    motor1.run(FORWARD);
    motor2.run(FORWARD);
  }
  else if(Carspeed < 0){
    motor1.run(BACKWARD);
    motor2.run(BACKWARD);
  }
  else{
    motor1.run(RELEASE);
    motor2.run(RELEASE);
  }

  Carspeed = abs(Carspeed);
  Carspeed = constrain(Carspeed, 0, 255);
  rot = constrain(rot,60, 120);

  motor1.setSpeed(Carspeed);
  motor2.setSpeed(Carspeed);
  Serial.println("Modo carro ativo com Velocidade: " + String(Carspeed) + " e Rotação: " + String(rot)); // DEBUG
    
  steering.write(rot);
}
