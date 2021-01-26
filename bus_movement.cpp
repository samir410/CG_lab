#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#include <windows.h>
#include <glut.h>
#define pi (2*acos(0.0))


double angle;
double incx=-30, incy;
int state;
struct point
{
	double x,y,z;
};
void draw_tri()
{
    glBegin(GL_POLYGON);
        glVertex2f(10, 10);
        glVertex2f(10, 0);
        glVertex2f(-10, 0);
    glEnd();
}
void push_pop(void)
{
    glPushMatrix();
        glRotatef(45, 0, 0, 1);

        glPushMatrix(); // Furthest Triangle, Draw first
            //glRotatef(45, 0, 0, 1);
            glTranslatef(-20, 0, 0);
            //glScaled(2, 1, 0);
            glColor3f(0.0, 0.0, 1.0);
            draw_tri();

        glPopMatrix();

        glPushMatrix(); // Middle Triangle, Draw 2nd
            glColor3f(0.0, 1.0, 0.0);
            draw_tri();
        glPopMatrix();

        glPushMatrix(); // Nearest Triangle, Draw last
            glTranslatef(20, 0, 0);
            glColor3f(1.0, 0.0, 0.0);
            draw_tri();
        glPopMatrix();


    glPopMatrix();

}


void drawAxes()
{

    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_LINES);{
        glVertex3f( 100,0,0);
        glVertex3f(-100,0,0);

        glVertex3f(0,-100,0);
        glVertex3f(0, 100,0);

        glVertex3f(0,0, 100);
        glVertex3f(0,0,-100);
    }glEnd();

}


void drawGrid()
{
	int i;

    glColor3f(0.6, 0.6, 0.6);	//grey
    glBegin(GL_LINES);{
        for(i=-8;i<=8;i++){

            if(i==0)
                continue;	//SKIP the MAIN axes

            //lines parallel to Y-axis
            glVertex3f(i*10, -90, 0);
            glVertex3f(i*10,  90, 0);

            //lines parallel to X-axis
            glVertex3f(-90, i*10, 0);
            glVertex3f( 90, i*10, 0);
        }
    }glEnd();

}

void drawSquare(double a)
{
    //glColor3f(1.0,0.0,0.0);
	glBegin(GL_QUADS);{
		glVertex3f( a/5, a,2);
		glVertex3f( a/5,-a,2);
		glVertex3f(-a/5,-a,2);
		glVertex3f(-a/5, a,2);
	}glEnd();
	glBegin(GL_QUADS);{
		glVertex3f( a, a/5,2);
		glVertex3f( a,-a/5,2);
		glVertex3f(-a,-a/5,2);
		glVertex3f(-a, a/5,2);
	}glEnd();
}


void drawCircle(float radius_x, float radius_y)
{
	int i = 0;
	float angle = 0.0;

	glBegin(GL_POLYGON);
    {
		for(i = 0; i < 100; i++)
		{
			angle = 2 * 3.1416 * i / 100;
			glVertex3f (cos(angle) * radius_x, sin(angle) * radius_y, 0);
		}

    }

	glEnd();
}
void draw_rec()
{
glColor3f(1.0,0.0,0.0);
glBegin(GL_QUADS);{
		glVertex3f( 45, 30,2);
		glVertex3f( 45,-10,2);
		glVertex3f(-15,-10,2);
		glVertex3f(-15, 30,2);

	}glEnd();

    //drawSquare(5);

}
void simple_trans()
{
    draw_rec();
}
void rec_animation()
{
     glPushMatrix();
      glColor3f(0,1,0);
         glTranslatef(incx,incy,0);
         glRotatef(5*angle,0,0,1);
         drawSquare(15);
     glPopMatrix();

     glPushMatrix();
         glColor3f(0,1,0);
         glTranslatef(incx+30,incy,0);
         glRotatef(5*angle,0,0,1);
         drawSquare(15);
     glPopMatrix();

    glPushMatrix();
      glTranslatef(incx,incy,0);
      simple_trans();
    glPopMatrix();
}

void drawSS()
{
    glColor3f(1,0,0);
    drawSquare(20);
    glPushMatrix();
    glRotatef(angle,0,0,1);
    glTranslatef(110,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,1,0);
    drawSquare(15);
    //glPopMatrix();

    glRotatef(angle,0,0,1);
    glTranslatef(60,0,0);
    glRotatef(2*angle,0,0,1);
    glColor3f(0,0,1);
    drawSquare(10);




}


double curve_by_points()
{
    ///
}
double func(double x)
{
    return x*x;
}
void curve()
{
    glColor3f(0.0f, 1.0f, 0.0f);
    glBegin(GL_LINES);
    for(double i =-180; i<180;i+=.5)
    {
        glVertex2d(i,10*func(i));
        glVertex2d(i+.5, 10*func(i+.5));
    }
     // It can be any type Gl_POINT,_LINE
    glEnd();

}
void display(){

	//clear the display
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0,0,0,0);	//color black
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);



	glMatrixMode(GL_MODELVIEW);


	glLoadIdentity();


	gluLookAt(0,0,100,	0,0,0,	0,1,0);



	glMatrixMode(GL_MODELVIEW);

	drawAxes();
	drawGrid();
    //simple_trans();
    //push_pop();
    rec_animation();







	//ADD this line in the end --- if you use double buffer (i.e. GL_DOUBLE)
	glutSwapBuffers();
}


void animate(){
    //rotation
    angle+=0.008;
    incx+=0.005;

	//codes for any changes in Models, Camera
	//linear_oscillation

    /*if(state ==0 && incx>50){ state =1;}
    if(state ==1 && incx <-50){state =0;}

    if(state == 0) incx+=0.05;
    else incx-=0.05;*/

	glutPostRedisplay();
}

void init(){
	//codes for initialization
	angle=0;

	//clear the screen
	glClearColor(0,0,0,0);


	//load the PROJECTION matrix
	glMatrixMode(GL_PROJECTION);

	//initialize the matrix
	glLoadIdentity();

	//give PERSPECTIVE parameters
	gluPerspective(80,	1,	1,	1000.0);

}

int main(int argc, char **argv){
	glutInit(&argc,argv);
	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGB);	//Depth, Double buffer, RGB color

	glutCreateWindow("My OpenGL Program");

	init();

	glEnable(GL_DEPTH_TEST);	//enable Depth Testing

	glutDisplayFunc(display);	//display callback function
	glutIdleFunc(animate);		//what you want to do in the idle time (when no drawing is occuring)

	//glutKeyboardFunc(keyboardListener);
	//glutSpecialFunc(specialKeyListener);
	//glutMouseFunc(mouseListener);

	glutMainLoop();		//The main loop of OpenGL

	return 0;
}

