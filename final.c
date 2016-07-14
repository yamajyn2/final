#include <stdlib.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include "myShape.h"

int xBegin, yBegin;
int mButton;
float distance, elevation, azimuth;
float rot=0.;
float x = 0,y=-17,z=0;
float light[] = {-1.0,1.0,1.0,0.0};

int i;



float shininess = 128.;

void scene(void){
	//color
	//initial
	float ambient[]  = { 0.3, 0.3, 0.3, 1.0 };//����
	float diffuse[] = { 0.8, 0.8, 0.8, 1.0 };//�g�U��
	float specular[] = { 0.0, 0.0, 0.0, 1.0 };//���ʔ���
	//ground
	float groundDif[] = { 160./255,160./255 , 160./255, 1.0 };
	//line
	float lineDif[] = { 100./255,100./255 , 100./255, 1.0 };
	float lineSpe[] = {0.8, 0.8, 0.8, 1.0};
	float makuraDif[] = { 70./255,30./255 , 0./255, 1.0 };
	//home
	float homeDif[] = { 180./255,180./255 , 210./255, 1.0 };

	//overheadLine
	float ovLineDif[] = { 180./255,180./255 , 210./255, 1.0 };

	glEnable(GL_DEPTH_TEST);
	glEnable( GL_LIGHTING );
	glLightfv( GL_LIGHT0,GL_POSITION,light);


	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_AMBIENT, ambient );
	glMaterialf( GL_FRONT, GL_SHININESS, shininess );
// ground
	   glMaterialfv( GL_FRONT, GL_DIFFUSE, groundDif );
	   glPushMatrix ();
	   glRotatef( -90., 1.0, 0.0, 0.0);
	   glNormal3f(0., 0., 1.);
	   glRecti(-5000,-5000, 5000,5000);
	   glPopMatrix ();


//line

	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, lineDif );
		glMaterialfv( GL_FRONT, GL_SPECULAR, lineSpe );
		glTranslatef( 0., 2.5, -10.0 );
		glScalef(10000, 2, 1 );
		glutSolidCube(1.0);
	glPopMatrix();

	glPushMatrix();
		glTranslatef( 0., 2.5, 10.0 );
		glScalef(10000,2, 1 );
		glutSolidCube(1.0);
	glPopMatrix();

	//makuragi
	glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
	glMaterialfv( GL_FRONT, GL_DIFFUSE, makuraDif );
	for(i=0; i<1000; i++){
		glPushMatrix();
			glTranslatef( i*20-500, 1, 0 );
			glScalef(6, 1, 30 );
			glutSolidCube(1.0);
		glPopMatrix();
	}
	//subline

		glPushMatrix();
			glMaterialfv( GL_FRONT, GL_DIFFUSE, lineDif );
			glMaterialfv( GL_FRONT, GL_SPECULAR, lineSpe );
			glTranslatef( 0., 2.5, -45.0 );
			glScalef(10000, 2, 1 );
			glutSolidCube(1.0);
		glPopMatrix();

		glPushMatrix();
			glTranslatef( 0., 2.5, -25.0 );
			glScalef(10000,2, 1 );
			glutSolidCube(1.0);
		glPopMatrix();

		//makuragi
		glMaterialfv( GL_FRONT, GL_SPECULAR, specular );
		glMaterialfv( GL_FRONT, GL_DIFFUSE, makuraDif );
		for(i=0; i<1000; i++){
			glPushMatrix();
				glTranslatef( i*20-500, 1, -35 );
				glScalef(6, 1, 30 );
				glutSolidCube(1.0);
			glPopMatrix();
		}

// home
glPushMatrix();
	glMaterialfv( GL_FRONT, GL_DIFFUSE, homeDif );
	glTranslatef( 0., 6, 32.0 );
	glScalef(2000, 12, 30 );
	glutSolidCube(1.0);

glPopMatrix();

//ovLine
for(i=0; i<100; i++){
	glPushMatrix();
		glMaterialfv( GL_FRONT, GL_DIFFUSE, ovLineDif );
		glTranslatef( i*100., 30, 32.0 );
		glScalef(1, 60, 1 );
		glutSolidCube(1.0);
	glPopMatrix();
}




	glDisable(GL_LIGHTING);
	glDisable(GL_DEPTH_TEST);
	glPopMatrix();

}


void display(void)
{
	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glPushMatrix ();
	glTranslatef( 0.0, 0.0, -distance);
	glRotatef( -elevation, 1.0, 0.0, 0.0);
	glRotatef( -azimuth, 0.0, 1.0, 0.0);
	glTranslatef( x, y, z);
	scene();
	glPopMatrix();
	glutSwapBuffers();
}

void idle(void)
{
	//x-=1;
	glutPostRedisplay();
	//�ϐ���ω�������
}

void initLighting(void){
	float diffuseL [] = {1.0,1.0,1.0,1.0};
	float specularL [] = {1.0,1.0,1.0,1.0};
	float ambientL [] = {0.5,0.5,0.5,1.0};

	glLightfv( GL_LIGHT0,GL_DIFFUSE,diffuseL);
	glLightfv( GL_LIGHT0,GL_SPECULAR,specularL);
	glLightfv( GL_LIGHT0,GL_AMBIENT,ambientL);
	glEnable( GL_LIGHT0);
}

void myMouse(int button, int state, int x, int y)
{
	if ( state == GLUT_DOWN )
	{      	xBegin = x;     yBegin = y;
        	mButton = button;
	}
}

void myMotion(int x, int y)
{
    	int xDisp, yDisp;

    	xDisp = x - xBegin;    	yDisp = y - yBegin;

    	switch(mButton)
	{
    	   case GLUT_LEFT_BUTTON:
		azimuth += (double) xDisp/5.0;
        	elevation -= (double) yDisp/5.0;
        	break;

    	   case GLUT_RIGHT_BUTTON:
        	distance -= (double) (xDisp + yDisp)/60.0;
        	break;
    	}
    	xBegin = x;    yBegin = y;

    	glutPostRedisplay();
}

void myInit (char *progname)
{
	int width = 1280, height = 720;

    glutInitWindowPosition(0, 0);
    glutInitWindowSize( width, height);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutCreateWindow(progname);
    glClearColor (0.0, 0.0, 0.0, 1.0);
   	glutMouseFunc( myMouse );
    glutMotionFunc( myMotion );

    	distance = 0;   elevation=0;    azimuth = -90;

	glShadeModel(GL_FLAT);
	initLighting();
}

void myReshape(int width, int height)
{
	float aspect = (float) width / (float) height;

	glViewport(0, 0, width, height);
    	glMatrixMode(GL_PROJECTION);
    	glLoadIdentity();
    	gluPerspective(50.0, aspect, 1.0, 3000.0);
    	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv)
{	glutInit(&argc, argv);
	myInit(argv[0]);
	glutReshapeFunc(myReshape);
	glutDisplayFunc(display);
	glutIdleFunc(idle);
	glutMainLoop();

	return(0);
}
