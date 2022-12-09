#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include<iostream>
#include<cstdlib>
#include<ctime>
#include <string>

using namespace std;
using namespace sf;

int main()
{
    //Init game const
    const double SCREEN_WIDTH=1200;
    const double SCREEN_HEIGH=600;
    const int borderLeft=400;
    const int borderRight=800;
    const int racerWidth=40;
    const int racerHeight=70;
    string stringscore="";
    int score=0;
    double gameSpeed=0.3;
    //bool startGame=false;
    bool gameOver=false;

    //Create Main Windows
    RenderWindow app(VideoMode(SCREEN_WIDTH, SCREEN_HEIGH), "Car Racing");

    //Init game music
    SoundBuffer gameSoundBuffer;
        gameSoundBuffer.loadFromFile("sound/game.wav");
    Sound GameSound;
        GameSound.setBuffer(gameSoundBuffer);

    Texture background, racer, obs1, obs2, obs3, obs4,gameover,coin;
    //Init font
    Font myfont;
    myfont.loadFromFile("font/xirod.ttf");

    //Load all images
    background.loadFromFile("cars/background.jpeg");
    racer.loadFromFile("cars/racer.png");
    obs1.loadFromFile("cars/obs1.png");
    obs2.loadFromFile("cars/obs2.png");
    obs3.loadFromFile("cars/obs3.png");
    obs4.loadFromFile("cars/obs4.png");
    coin.loadFromFile("Sources/coin.png");

    //Create sprite
    Sprite Background(background),Background1(background),Racer(racer),Obs1(obs1),Obs2(obs2),Obs3(obs3),Obs4(obs4),Gameover(gameover),Coin(coin);


    double RacerX, RacerY,Obs1X, Obs1Y,Obs2X, Obs2Y,Obs3X, Obs3Y,Obs4X, Obs4Y, CoinX, CoinY;

    //Set racer and Obs pos
	RacerX=SCREEN_WIDTH/2;
	RacerY=SCREEN_HEIGH-racerHeight;
	Obs1X=rand()%borderRight+borderLeft;
	Obs2X=rand()%borderRight+borderLeft;
	Obs3X=rand()%borderRight+borderLeft;
	Obs4X=rand()%borderRight+borderLeft;
	CoinX=rand()%borderRight+borderLeft;
    Obs1Y=0,Obs2Y=-100,Obs3Y=-200,Obs4Y=-300,CoinY=-400;
    double BackgroundY1=0;
    double BackgroundY2=-600;

    GameSound.play();
    GameSound.setLoop(true);


	// Start the game loop
    while (app.isOpen())
    {
        // Process events
        sf::Event event;
        while (app.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                app.close();
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                app.close();
            //if(event.type==sf::Event::MouseButtonPressed)
                //startGame=true;

            if (event.type == sf::Event::KeyPressed&&gameOver==false)
                {
                    if (event.key.code == sf::Keyboard::Left)
                        {if(RacerX>borderLeft) {RacerX=RacerX-10;}}
                    if (event.key.code == sf::Keyboard::Right)
                        {if(RacerX<borderRight){RacerX=RacerX+10;}}
                    if (event.key.code == sf::Keyboard::Up)
                        {if(RacerY>0){RacerY=RacerY-10;}}
                    if (event.key.code == sf::Keyboard::Down)
                        {if(RacerY<SCREEN_HEIGH-70){RacerY=RacerY+10;}}
                }
        }

        //Init and count score
        stringscore="SCORE:"+to_string(score);
        Text text(stringscore, myfont, 15);
        text.setPosition(5,0);

        //Set car position
        Racer.setPosition(RacerX,RacerY);
        Obs1.setPosition(Obs1X,Obs1Y);
        Obs2.setPosition(Obs2X,Obs2Y);
        Obs3.setPosition(Obs3X,Obs3Y);
        Obs4.setPosition(Obs4X,Obs4Y);
        Coin.setPosition(CoinX,CoinY);

        //Creat scrolling background
        Background.setPosition(0,BackgroundY1);
        Background1.setPosition(0,BackgroundY2);
        if (BackgroundY2>0)
        {
            BackgroundY1=0;
            BackgroundY2=BackgroundY1-500;
        }
        BackgroundY1+=0.1;
        BackgroundY2+=0.1;

        //Set Obs LOOP
        if (Obs1Y>SCREEN_HEIGH)
            {Obs1Y=0;Obs1X=rand()%borderRight+borderLeft;} else {Obs1Y=Obs1Y+gameSpeed;}
        if (Obs2Y>SCREEN_HEIGH)
            {Obs2Y=0;Obs2X=rand()%borderRight+borderLeft;} else {Obs2Y=Obs2Y+gameSpeed;}
        if (Obs3Y>SCREEN_HEIGH)
            {Obs3Y=0;Obs3X=rand()%borderRight+borderLeft;} else {Obs3Y=Obs3Y+gameSpeed;}
        if (Obs4Y>SCREEN_HEIGH)
            {Obs4Y=0;Obs4X=rand()%borderRight+borderLeft;} else {Obs4Y=Obs4Y+gameSpeed;}
        if (CoinY>SCREEN_HEIGH)
            {CoinY=0;CoinX=rand()%borderRight+borderLeft;} else {CoinY=CoinY+gameSpeed;}
        if (Coin.getGlobalBounds().intersects(Racer.getGlobalBounds())==true)
            {CoinY=0;CoinX=rand()%borderRight+borderLeft;score++;}

        //Game level
        if(score>10 && score<18) {gameSpeed=0.4;}
        if(score>18 && score<25) {gameSpeed=0.5;}
        if(score>25 && score<35) {gameSpeed=0.6;}

        if (Racer.getGlobalBounds().intersects(Obs1.getGlobalBounds())==true||Racer.getGlobalBounds().intersects(Obs2.getGlobalBounds())==true||Racer.getGlobalBounds().intersects(Obs3.getGlobalBounds())==true||Racer.getGlobalBounds().intersects(Obs4.getGlobalBounds())==true)
            {
                GameSound.stop();
                gameOver=true;
            };

        if(gameOver==false){
            app.clear();
            app.draw(Background);
            app.draw(Background1);
            app.draw(Racer);
            app.draw(Obs1);
            app.draw(Obs2);
            app.draw(Obs3);
            app.draw(Obs4);
            app.draw(Coin);
            app.draw(text);
            app.display();
        }

        else{
            Texture gameover;
            gameover.loadFromFile("cars/over.png");

            Sprite Gameover(gameover);
            Gameover.setPosition(300,50);;
            SoundBuffer gameOver;
               gameOver.loadFromFile("sound/crash.wav");
            Sound GameOver;
                GameOver.setBuffer(gameOver);
                GameOver.play();
            while (app.isOpen())
            {
                Event event;
                while (app.pollEvent(event))
                {
                    if (event.type == Event::Closed)
                    app.close();
                }
                Font myfont;
                    myfont.loadFromFile("font/xirod.ttf");
                    stringscore="YOUR SCORE:"+to_string(score);
                Text text(stringscore, myfont, 30);
                    text.setPosition(210,450);
                app.clear();
                app.draw(Gameover);
                app.draw(text);
                app.display();

            }
        }
    }

    return EXIT_SUCCESS;
}
