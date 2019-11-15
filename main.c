/* TeaPot3D.c (Isabel Harb Manssour)
 Exemplo de visualização de objetos 3D
 Baseado nos exemplos do livro OpenGL SuperBible, 2nd Edition
 Richard S. Wright Jr.
*/
#include <stdio.h>
#include <GL/freeglut.h>
#include <math.h>


//Constantes
const int SCREEN_WIDTH = 600;
const int SCREEN_HEIGHT = 600;

double angx=0;
double angy=0;
double angz=0;
double angbracocimaesq = 0;
double angbracocimadir = 0;

GLfloat angle = 75.0;
GLfloat fAspect;

GLfloat angulo_dir_minion1 = 0.0f; //PE
GLfloat angulo_esq_minion1 = 0.0f;
GLfloat ang_step_minion1_pe = 1.0f;

GLfloat angulo_dir_minion2 = 0.0f;  //PE
GLfloat angulo_esq_minion2 = 0.0f;
GLfloat ang_step_minion2_pe = 1.0f;

GLfloat angulo_dir_minion1_braco_cima = 0.0f;    //BRACO CIMA
GLfloat angulo_esq_minion1_braco_cima = 0.0f;
GLfloat ang_step_minion1_braco_cima = 1.0f;

GLfloat angulo_dir_minion2_braco_cima = 0.0f;
GLfloat angulo_esq_minion2_braco_cima = 0.0f;
GLfloat  ang_step_minion2_braco_cima = 1.0f;

GLfloat angulo_dir_minion1_braco_baixo = 0.0f;
GLfloat angulo_esq_minion1_braco_baixo = 0.0f;
GLfloat ang_step_minion1_braco_baixo = 1.0f;
float passoRL = 1.0;
GLfloat passoL = 1.0;
float passoUD = 1.0;
GLfloat passoD = 1.0;
float anguloRL = 0.0;

double speed = 5;
double radian;
double rot; // Angulo de Rotação

float win=10, anglex = 0.0, angley = 0.0, anglez = 0.0, panX=0.0, panY=0.0;

// Estrutura de dados
typedef struct _Vector{
   double x,y,z;
} Vector;

// Vetores
Vector pos;
Vector vel;
Vector dir;
Vector dis;
Vector mouseCoords;


#define MIN_COORDINATE 0.0
#define MAX_COORDINATE 1.0

#define U_STRIDE 3

#define MAX_U_NUMBER 20
#define MAX_V_NUMBER 20

#define MIN_U_NUMBER 0
#define MIN_V_NUMBER 0

#define BOCA_LINE   5
#define BOCA_COLUMN 3
#define POINT_DIMENSION 3


GLfloat boca_ctrl_points[BOCA_LINE][BOCA_COLUMN][POINT_DIMENSION] =
        {
                {{-13.00, 3.00, 3.00}, {2.0, 4.00, -9.00}, {10.0, -8.00, -2.00}, {-10.0, 10.00, -10.00}, {-8.0, 3.00, 0.00}}

        };

void plot_ctrl_points(int n_column, int n_line, int point_size, GLfloat** ctrl_points)
{
    int i, j;

    glPointSize(point_size);

    glBegin(GL_POINTS);

    for (i = 0; i < n_line; i++)
    {
        for (j = 0; j < n_column; j++)
        {
            glColor3f(1, 1, 1);
            glVertex3fv(&ctrl_points[i][j]);
        }
    }

    glEnd();
}

void init_spline(int n_columns, int n_lines, GLfloat* ctrl_points)
{
    glMap2f(GL_MAP2_VERTEX_3, MIN_COORDINATE, MAX_COORDINATE, U_STRIDE, n_columns, MIN_COORDINATE,
            MAX_COORDINATE, n_columns * U_STRIDE, n_lines, (const GLfloat *) ctrl_points);

    glEnable(GL_MAP2_VERTEX_3);
}

void execute_spline(int n_columns, int n_lines, GLfloat* ctrl_points)
{
    init_spline(n_columns, n_lines, ctrl_points);
    glMapGrid2f(MAX_U_NUMBER, MIN_COORDINATE, MAX_COORDINATE, MAX_V_NUMBER, MIN_COORDINATE, MAX_COORDINATE);
    glEvalMesh2(GL_FILL, MIN_U_NUMBER, MAX_U_NUMBER, MIN_V_NUMBER, MAX_V_NUMBER);
}

void fundo(){

    //Rua
    glPushMatrix();
        glColor3f(0.8, 0.8, 0.8);
        glTranslated(0.0, -100.0, 0.0);
        glScaled(70.0, 0.0, 50.0);
        glutSolidCube(20);
    glPopMatrix();

}


void casaGru(){

//CASA DO GRU
glPushMatrix();
    glTranslated(0.0, 0.0, -50);
//fundo da casa
glPushMatrix();
    glColor3f(0.25, 0.0, 0.25);
    glTranslated(80.0, 20.0, -140.0);
    glScaled(10.0, 11.0, 3.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.25, 0.0, 0.25);
    glTranslated(-110.0, 20.0, -140.0);
    glScaled(10.0, 11.0, 3.0);
    glutSolidCube(20);
glPopMatrix();

//telhado dos fundos
//direito
glPushMatrix();
    glColor3f(0.2, 0.0, 0.0);
    glTranslated(90.0, 170.0, -150.0);
    glScaled(6.0, 6.0, 3.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.0, 0.0);
    glTranslated(162.0, 118.0, -150.0);
    glScaled(3.0, 6.0, 0.1);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(180, 0.0, 1.0, 0.0);
    glutSolidCone(20, 20, 50, 50);
glPopMatrix();

//esquerdo
glPushMatrix();
    glColor3f(0.2, 0.0, 0.0);
    glTranslated(-80.0, 170.0, -150.0);
    glScaled(10.0, 6.0, 2.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.0, 0.0);
    glTranslated(-189.0, 117.0, -150.0);
    glScaled(3.0, 6.0, 0.1);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(180, 0.0, 1.0, 0.0);
    glutSolidCone(20, 20, 50, 50);
glPopMatrix();

//Janelas
//Esquerda
//Vidro
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(-160.0, 165.0, -115.0);
    glScaled(1.0, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-170.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-150.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 200.0,-110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 205.0, -110.0);
    glScaled(1.3, 0.4, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 130.0, -110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 125.0, -110.0);
    glScaled(1.3, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 165.0, -110.0);
    glScaled(0.1, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 180.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 160.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-160.0, 145.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//janela direita
//Vidro
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(-120.0, 165.0, -115.0);
    glScaled(1.0, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-130.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-110.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 200.0, -110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 205.0, -110.0);
    glScaled(1.3, 0.4, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 130.0, -110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 125.0, -110.0);
    glScaled(1.3, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 165.0, -110.0);
    glScaled(0.1, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 180.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 160.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-120.0, 145.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//lado esquerdo
//parte reta
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-150.0, -20.0, -110.0);
    glScaled(3.0, 7.0, 0.1);
    glutSolidCube(20);
glPopMatrix();

//INSERIR CIRCUNFERENCIA AQUI

//janela fundo direita
//Vidro
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(140.0, 0.0, -108.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(155.0, 0.0, -105.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(125.0, 0.0, -105.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, 50.0, -105.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, 55.0, -105.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, -50.0, -105.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, -58.0, -105.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, 0.0, -105.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, 30.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, 8.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, -14.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, -36.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//frente
glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(-47.0, 60.0, -150.0);
    glScaled(10.0, 10.0, 10.0);
    glutSolidCube(10);
glPopMatrix();

glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(47.0, 60.0, -150.0);
    glScaled(10, 10, 10);
    glutSolidCube(10);
glPopMatrix();

glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(-50.0, -40.0, -150.0);
    glScaled(10, 10, 10);
    glutSolidCube(10);
glPopMatrix();

glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(50.0, -40.0, -150.0);
    glScaled(10, 10, 10);
    glutSolidCube(10);
glPopMatrix();

//triangulo do telhado
glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(0.0, 110.0, -135.0);
    glScaled(10, 9, 6);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(180, 0.0, 1.0, 0.0);
    glutSolidCone(10, 20, 50, 50);
glPopMatrix();

//janela de bolinha
//bolinha
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(0.0, 225.0, -100.0);
    glScaled(1.0, 1.0, 0.0);
    glutSolidSphere(20.0, 50, 50);
glPopMatrix();

//tracos
glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(0.0, 221.0, -90.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(0.0, 221.0, -90.0);
    glRotated(90, 0.0, 0.0, 1.0);
    glScaled(0.1, 2.5, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(0.0, 221.0, -90.0);
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.3, 0.0, 0.3);
    glTranslated(0.0, 221.0, -90.0);
    glRotated(135, 0.0, 0.0, 1.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura telhado - esquerda
glPushMatrix();
    glColor3f(0.2, 0.0, 0.0);
    glTranslated(-60.0, 185.0, -110.0);
    glRotated(60.0, 0.0, 0.0, 1.0);
    glScaled(12.0, 0.5, 3.0);
    glutSolidCube(20);
glPopMatrix();

//direita
glPushMatrix();
    glColor3f(0.2, 0.0, 0.0);
    glTranslated(60.0, 185.0, -110.0);
    glRotated(-60.0, 0.0, 0.0, 1.0);
    glScaled(12.0, 0.5, 3.0);
    glutSolidCube(20);
glPopMatrix();

//Porta da frente
glPushMatrix();
    glColor3f(0.6, 0.0, 0.0);
    glTranslated(0.0, -30.0, -95.0);
    glScaled(3.0, 6.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Detalhes da porta
//Superior esquerdo
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-22.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-3.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, 19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, -19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Superior direito
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(22.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(3.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, 19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, -19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Inferior esquerdo
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-22.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-3.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, -31.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, -69.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Inferior direito
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(22.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(3.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, -31.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, -69.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Maçaneta
glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslated(-27.0, -25.0, -95.0);
    glScaled(0.2, 0.5, 0.1);
    glutSolidCube(20);
glPopMatrix();

//Escadas
//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, -90.0, -98.0);
    glScaled(3.0, 0.8, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, -100.0, -105.0);
    glScaled(3.0, 0.8, 0.8);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, -110.0, -100.0);
    glScaled(3.0, 0.8, 0.5);
    glutSolidCube(20);
glPopMatrix();


//Janela Direita
//Vidro
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(65.0, 0.0, -95.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(50.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-82.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, 50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, 55.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, -50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, -58.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, 0.0, -90.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, 30.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, 8.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, -14.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, -36.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Janela esquerda
//Vidro
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(-65.0, 0.0, -95.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura da janela
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-50.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(80.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, 50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, 55.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, -50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(65.0, -55.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, 0.0, -90.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, 30.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, 8.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, -14.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-65.0, -36.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Janela segundo andar
//Vidro
glPushMatrix();
    glColor3f(0.2, 0.4, 0.5);
    glTranslated(0.0, 130.0, -75.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(15.0, 130.0, -70.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(-15.0, 130.0, -70.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 180.0, -80.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 185.0, -80.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 85.0, -75.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 80.0, -80.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 135.0, -74.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 100.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 120.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 140.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(0.0, 160.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();
glPopMatrix();
}

static void draw_generic_forearm()
{
    execute_spline(BOCA_COLUMN, BOCA_LINE, (GLfloat *) boca_ctrl_points);
}

//Função que desenha Minion Bob
void Minion1(){
glPushMatrix();
glTranslated(0.0, 20.0, 0.0);
    //Cilindro corpo baixo
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -40.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(2.3, 2.2, 2.3);
        glutSolidCylinder(20.0, 20.0, 50, 50);
    glPopMatrix();


    //Corpo
    glPushMatrix();
        glColor3f(0.9, 1.0, 0.1);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(2.35, 2.3, 3.3);
        glutSolidCylinder(20.0, 15.0, 50.0, 50.0);
    glPopMatrix();

    //cabeça
    glPushMatrix();
        glColor3f(0.9, 1.0, 0.1);
        glTranslated(0.0, -8.0, 0.0);
        glScaled(2.35, 2.35, 2.35);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //Parte do bolsinho - frente
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -30.0, 39.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(1.8, 0.4, 2.0);
        glutSolidCylinder(20.0, 10.0, 50, 50);
    glPopMatrix();

    //Simbolo Gru - circulo fora
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 47.5);
        glScaled(1.0, 1.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

    //Simbolo Gru - quadrado
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -45.0, 49.0);
        glRotated(45, 0.0, 0.0, 1.0);
        glScaled(1.0, 1.0, 0.0);
        glutSolidCube(10);
    glPopMatrix();

    //Simbolo Gru - circulo dentro
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 50.5);
        glScaled(1.0, 1.0, 0.0);
        glutSolidSphere(3.0, 100, 100);
    glPopMatrix();

    //Simbolo Gru - Traco quadrado (cor da roupa)
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(4.3, -45.5, 51.0);
        glScaled(4.0, 0.5, 0.0);
        glutSolidCube(2.0);
    glPopMatrix();

    //Simbolo Gru - Traco circulo (preto)
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(4.3, -44.5, 51.0);
        glScaled(4.0, 0.5, 0.0);
        glutSolidCube(2.0);
    glPopMatrix();


    //Parte do bolsinho - tras
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -30.0, -39.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(1.7, 0.4, 2.0);
        glutSolidCylinder(20.0, 10.0, 50, 50);
    glPopMatrix();


    //alca da roupinha - direita
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(35.7, -30.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glRotated(30.0, 1.0, 0.0, 0.0);
        glScaled(2.3, 1.0, 1.0);
        glutSolidTorus(2.0, 20.0, 100, 100);
    glPopMatrix();

    //botao roupa - direita
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(30.0, -33.0, 50.0);
        glScaled(0.2, 0.2, 0.2);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //alca da roupinha - esquerda
     glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(-35.7, -30.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glRotated(-30.0, 1.0, 0.0, 0.0);
        glScaled(2.3, 1.0, 1.0);
        glutSolidTorus(2.0, 20.0, 100, 100);
    glPopMatrix();

    //Botao da roupa - esquerda
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-30.0, -33.0, 50.0);
        glScaled(0.2, 0.2, 0.2);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //Braço bolinha esquerda
glPushMatrix(); //PARA MEXER TUDO
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -30.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //PARA MEXER BRACO CIMA
glTranslated(-50.0, -30.0, 0.0);
glRotated(angulo_dir_minion1_braco_cima, 1.0, 0.0, 0.0);
glTranslated(50.0, 30.0, 0.0);
//braço longo cima
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -30.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(8.0, 20.0, 100, 100);
    glPopMatrix();

//bolinha cotovelo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -50.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //PARA MEXER BRACO BAIXO
glTranslated(-50.0, -50.0, 0.0);
glRotated(angulo_dir_minion1_braco_baixo, 1.0, 0.0, 0.0);
glTranslated(50.0, 50.0, 0.0);
//reto bracinho baixo
    glPushMatrix(); //PARA MEXER MAO
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslated(50.0, -50.0, 0.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 15.0, 100, 100);
        glPopMatrix();

//Luvinha borda
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidTorus(2.0, 8.0, 100, 100);
        glPopMatrix();

//luvinha pulso
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 6.0, 100, 100);
        glPopMatrix();

//Palma da mao
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -59.0, 18.0);
            glutSolidSphere(7.0, 100, 100);
        glPopMatrix();

//dedo 1
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(40.0, -55.0, 15.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 2
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(55.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 3
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(46.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();
    glPopMatrix(); //PARA MEXER MAO
    glPopMatrix(); //PARA MEXER BRACO BAIXO
    glPopMatrix(); //PARA MEXER BRACO CIMA
glPopMatrix(); //PARA MEXER TUDO

//Braço bolinha esquerda
glPushMatrix(); //PARA MEXER TUDO
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -30.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix();// PARA MEXER O BRACO CIMA
    glTranslated(-50.0, -30.0, 0.0);
    glRotated(angulo_esq_minion1_braco_cima, 1.0, 0.0, 0.0);
    glTranslated(50.0, 30.0, 0.0);
    //braço longo cima
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -30.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(8.0, 20.0, 100, 100);
    glPopMatrix();

//bolinha cotovelo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -50.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //PARA MEXER BRACO BAIXO
glTranslated(-50.0, -50.0, 0.0);
glRotated(angulo_esq_minion1_braco_baixo, 1.0, 0.0, 0.0);
glTranslated(50.0, 50.0, 0.0);
//reto bracinho baixo
    glPushMatrix(); //PARA MEXER MAO
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslated(-50.0, -50.0, 0.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 15.0, 100, 100);
        glPopMatrix();

//Luvinha borda
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidTorus(2.0, 8.0, 100, 100);
        glPopMatrix();

//luvinha pulso
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 6.0, 100, 100);
        glPopMatrix();

//Palma da mao
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -59.0, 18.0);
            glutSolidSphere(7.0, 100, 100);
        glPopMatrix();

//dedo 1
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-40.0, -55.0, 15.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 2
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-55.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 3
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-46.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();
    glPopMatrix(); //PARA MEXER MAO
glPopMatrix(); //PARA MEXER BRACO BAIXO
glPopMatrix(); //PARA MEXER BRACO CIMA
glPopMatrix(); //PARA MEXER TUDO




    //Perna direita

    glPushMatrix();
    glRotated(angulo_dir_minion1, 1.0, 0.0, 0.0);
        glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(-15.0, -80.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(10.0, 28.0, 100, 100);
        glPopMatrix();

        //Sapato esquerdo - base
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15.0, -115.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato esquerdo - calcanhar
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15, -105.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

     //Sapato esquerdo - bolinha da frente
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15.0, -115.0, 17.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    glPopMatrix();

    //Perna esquerda
    glPushMatrix();
    glRotated(angulo_esq_minion1, 1.0, 0.0, 0.0);
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(15.0, -80.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(10.0, 28.0, 100, 100);
    glPopMatrix();

        //Sapato direito - base
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15.0, -115.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato direito - calcanhar
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15, -105.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato direito - bolinha da frente
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15.0, -115.0, 17.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();
    glPopMatrix();


    //Olho esquerdo - bolinha branca
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(-14.0, 10.0, 40);
        glutSolidSphere(14.0, 100, 100);
    glPopMatrix();

    //Bolinha esquerda marrom escura do olho
    glPushMatrix();
        glColor3f(0.3, 0.2, 0.1);
        glTranslated(-14.0, 10.5, 50);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    //Olho direito - bolinha branca
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(14.0, 10.0, 40);
        glutSolidSphere(14.0, 100, 100);
    glPopMatrix();

     //Bolinha direita marrom escura do olho
    glPushMatrix();
        glColor3f(0.3, 0.2, 0.1);
        glTranslated(14.0, 10.5, 50);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    //Oculos lado direito
    glPushMatrix();
        glColor3f(0.6, 0.6, 0.5);
        glTranslated(15.0, 10.0, 40.0);
        glScaled(1.5, 1.5, 5.0);
        glutSolidTorus(1.5, 10.0, 100, 100);
    glPopMatrix();

    //Oculos lado esquerdo
    glPushMatrix();
        glColor3f(0.6, 0.6, 0.5);
        glTranslated(-15.0, 10.0, 40.0);
        glScaled(1.5, 1.5, 5.0);
        glutSolidTorus(1.5, 10.0, 100, 100);
    glPopMatrix();

    //Elastico do oculos
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, 10.0, -1.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(4.5, 4.5, 4.5);
        glutSolidTorus(0.5, 10.0, 100, 100);
    glPopMatrix();

//Boca
glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(0.0, -14.0, 46.8);
    glRotated(20, 0.0, 1.0, 0.0);
    glRotated(220.0, 1.0, 0.0, 0.0);
    //glScaled(1.0, 0.0, 0.0);
    draw_generic_forearm();
glPopMatrix();

glPopMatrix();
}

void Minion2(){
    glPushMatrix();
glTranslated(0.0, 20.0, 0.0);
    //Cilindro corpo baixo
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -40.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(2.3, 2.2, 2.3);
        glutSolidCylinder(20.0, 20.0, 50, 50);
    glPopMatrix();


    //Corpo
    glPushMatrix();
        glColor3f(0.9, 1.0, 0.1);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(2.35, 2.3, 3.3);
        glutSolidCylinder(20.0, 15.0, 50.0, 50.0);
    glPopMatrix();

    //cabeça
    glPushMatrix();
        glColor3f(0.9, 1.0, 0.1);
        glTranslated(0.0, -6.0, 0.0);
        glScaled(2.35, 2.35, 2.35);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //Parte do bolsinho - frente
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -30.0, 39.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(1.8, 0.4, 2.0);
        glutSolidCylinder(20.0, 10.0, 50, 50);
    glPopMatrix();

    //Simbolo Gru - circulo fora
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 47.5);
        glScaled(1.0, 1.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

    //Simbolo Gru - quadrado
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -45.0, 49.0);
        glRotated(45, 0.0, 0.0, 1.0);
        glScaled(1.0, 1.0, 0.0);
        glutSolidCube(10);
    glPopMatrix();

    //Simbolo Gru - circulo dentro
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 50.5);
        glScaled(1.0, 1.0, 0.0);
        glutSolidSphere(3.0, 100, 100);
    glPopMatrix();

    //Simbolo Gru - Traco quadrado (cor da roupa)
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(4.3, -45.5, 51.0);
        glScaled(4.0, 0.5, 0.0);
        glutSolidCube(2.0);
    glPopMatrix();

    //Simbolo Gru - Traco circulo (preto)
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(4.3, -44.5, 51.0);
        glScaled(4.0, 0.5, 0.0);
        glutSolidCube(2.0);
    glPopMatrix();


    //Parte do bolsinho - tras
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(0.0, -30.0, -39.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(1.7, 0.4, 2.0);
        glutSolidCylinder(20.0, 10.0, 50, 50);
    glPopMatrix();


    //alca da roupinha - direita
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(35.7, -30.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glRotated(30.0, 1.0, 0.0, 0.0);
        glScaled(2.3, 1.0, 1.0);
        glutSolidTorus(2.0, 20.0, 100, 100);
    glPopMatrix();

    //botao roupa - direita
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(30.0, -33.0, 50.0);
        glScaled(0.2, 0.2, 0.2);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //alca da roupinha - esquerda
     glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(-35.7, -30.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glRotated(-30.0, 1.0, 0.0, 0.0);
        glScaled(2.3, 1.0, 1.0);
        glutSolidTorus(2.0, 20.0, 100, 100);
    glPopMatrix();

    //Botao da roupa - esquerda
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-30.0, -33.0, 50.0);
        glScaled(0.2, 0.2, 0.2);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //Braço bolinha esquerda
glPushMatrix(); //Para mexer o braco todo

    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -30.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //Para mexer braco cima
glTranslated(-50.0, -30.0, 0.0);
glRotated(angulo_esq_minion1_braco_cima, 1.0, 0.0, 0.0);
glTranslated(50.0, 30.0, 0.0);
//braço longo cima
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -30.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(8.0, 20.0, 100, 100);
    glPopMatrix();

//bolinha cotovelo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -50.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //Para mexer braco baixo
glTranslated(-50.0, -50.0, 0.0);
glRotated(angulo_esq_minion1_braco_baixo, 1.0, 0.0, 0.0);
glTranslated(50.0, 50.0, 0.0);
//reto bracinho baixo
    glPushMatrix();

        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslated(50.0, -50.0, 0.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 15.0, 100, 100);
        glPopMatrix();

//Luvinha borda
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidTorus(2.0, 8.0, 100, 100);
        glPopMatrix();

//luvinha pulso
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 6.0, 100, 100);
        glPopMatrix();

//Palma da mao
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -59.0, 18.0);
            glutSolidSphere(7.0, 100, 100);
        glPopMatrix();

//dedo 1
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(40.0, -55.0, 15.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 2
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(55.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 3
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(46.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();
    glPopMatrix(); //Para mexer braco baixo
    glPopMatrix(); //Para mexer braco cima
    glPopMatrix();  //Para mexer toda a mao
glPopMatrix(); //Para mexer o braco todo

//Braço bolinha direita
glPushMatrix(); //Para mexer tudo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -30.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();
    glPushMatrix();

glPushMatrix(); //Para mexer braco cima

glTranslated(-50.0, -30.0, 0.0);
    glRotated(angulo_dir_minion1_braco_cima, 1.0, 0.0, 0.0);
glTranslated(50.0, 30.0, 0.0);

//braço longo cima
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -30.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(8.0, 20.0, 100, 100);
    glPopMatrix();

//bolinha cotovelo
    glPushMatrix();
       glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -50.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //Para mexer braco baixo
glTranslated(-50.0, -50.0, 0.0);
    glRotated(angulo_dir_minion1_braco_baixo, 1.0, 0.0, 0.0);
glTranslated(50.0, 50.0, 0.0);

//reto bracinho baixo
    glPushMatrix();
        glPushMatrix();
           glColor3f(1.0, 1.0, 0.0);
            glTranslated(-50.0, -50.0, 0.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 15.0, 100, 100);
        glPopMatrix();

//Luvinha borda
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidTorus(2.0, 8.0, 100, 100);
        glPopMatrix();

//luvinha pulso
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 6.0, 100, 100);
        glPopMatrix();

//Palma da mao
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -59.0, 18.0);
            glutSolidSphere(7.0, 100, 100);
        glPopMatrix();

//dedo 1
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-40.0, -55.0, 15.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 2
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-55.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 3
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-46.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();
    glPopMatrix();
    glPopMatrix(); //Para mexer braco baixo
    glPopMatrix(); //Para mexer braco cima
glPopMatrix(); //Para mexer tudo

    //Perna direita

    glPushMatrix();
    glRotated(angulo_dir_minion1, 1.0, 0.0, 0.0);
        glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(-15.0, -80.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(10.0, 28.0, 100, 100);
        glPopMatrix();

        //Sapato esquerdo - base
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15.0, -115.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato esquerdo - calcanhar
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15, -105.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

     //Sapato esquerdo - bolinha da frente
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15.0, -115.0, 17.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    glPopMatrix();

    //Perna esquerda
    glPushMatrix();
    glRotated(angulo_esq_minion1, 1.0, 0.0, 0.0);
    glPushMatrix();
        glColor3f(0.4, 0.3, 0.8);
        glTranslated(15.0, -80.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(10.0, 28.0, 100, 100);
    glPopMatrix();

        //Sapato direito - base
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15.0, -115.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato direito - calcanhar
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15, -105.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato direito - bolinha da frente
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15.0, -115.0, 17.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();
    glPopMatrix();

//Um olho só
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(0.0, 10.0, 35);
        glutSolidSphere(20.0, 100, 100);
    glPopMatrix();

//bolinha castanha
    glPushMatrix();
        glColor3f(0.3, 0.2, 0.1);
        glTranslated(0.0, 14.0, 48);
        glutSolidSphere(10.0, 100, 100);
    glPopMatrix();

//oculos
    glPushMatrix();
        glColor3f(0.6, 0.6, 0.5);
        glTranslated(0.0, 14.0, 40.0);
        glRotated(-20, 1.0, 0.0, 0.0);
        glutSolidTorus(2.5, 20.0, 100, 100);
    glPopMatrix();


    //Elastico do oculos
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, 10.0, -1.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(4.5, 4.5, 4.5);
        glutSolidTorus(0.5, 10.0, 100, 100);
    glPopMatrix();

//Cabelo
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-12.0, 19.0, 15.0);
        glutSolidTorus(1.5, 20.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-10.0, 21.0, 0.0);
        glutSolidTorus(1.5, 20.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-12.0, 20.0, -15.0);
        glutSolidTorus(1.5, 20.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(12.0, 19.0, 15.0);
        glutSolidTorus(1.5, 20.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(10.0, 21.0, 0.0);
        glutSolidTorus(1.5, 20.0, 100, 100);
    glPopMatrix();

    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(12.0, 20.0, -15.0);
        glutSolidTorus(1.5, 20.0, 100, 100);
    glPopMatrix();

//Boca
glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(0.0, -15.0, 46.0);
    glRotated(22, 0.0, 1.0, 0.0);
    glRotated(220.0, 1.0, 0.0, 0.0);
    //glScaled(1.0, 0.0, 0.0);
    draw_generic_forearm();
glPopMatrix();

glPopMatrix();
}

void Minion1Natal(){
    glPushMatrix();
glTranslated(0.0, 20.0, 0.0);
    //Cilindro corpo baixo
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(0.0, -40.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(2.3, 2.2, 2.3);
        glutSolidCylinder(20.0, 20.0, 50, 50);
    glPopMatrix();


    //Corpo
    glPushMatrix();
        glColor3f(0.9, 1.0, 0.1);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(2.35, 2.3, 3.3);
        glutSolidCylinder(20.0, 15.0, 50.0, 50.0);
    glPopMatrix();

    //cabeça
    glPushMatrix();
        glColor3f(0.9, 1.0, 0.1);
        glTranslated(0.0, -8.0, 0.0);
        glScaled(2.35, 2.35, 2.35);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();


    glPushMatrix(); //Para mexer todo o chapeu
    //Cone do Chapeu
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(0.0, 25.0, 0.0);
        glRotated(-90, 1.0, 0.0, 0.0);
        glutSolidCone(40.0, 55.5, 100, 100);
    glPopMatrix();

    //Torus em volta
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(0.0, 26.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidTorus(4.5, 40.0, 100, 100);
    glPopMatrix();

    //Bolinha
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(0.0, 70.0, 0.0);
        glutSolidSphere(17.0, 100, 100);
    glPopMatrix();
    glPushMatrix(); //Para mexer todo o chapeu

    //Parte do bolsinho - frente
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(0.0, -30.0, 39.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(1.8, 0.4, 2.0);
        glutSolidCylinder(20.0, 10.0, 50, 50);
    glPopMatrix();

    //Simbolo Gru - circulo fora
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 47.5);
        glScaled(1.0, 1.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

    //Simbolo Gru - quadrado
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 49.0);
        glRotated(45, 0.0, 0.0, 1.0);
        glScaled(1.0, 1.0, 0.0);
        glutSolidCube(10);
    glPopMatrix();

    //Simbolo Gru - circulo dentro
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, -45.0, 50.5);
        glScaled(1.0, 1.0, 0.0);
        glutSolidSphere(3.0, 100, 100);
    glPopMatrix();

    //Simbolo Gru - Traco quadrado (cor da roupa)
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(4.3, -45.5, 51.0);
        glScaled(4.0, 0.5, 0.0);
        glutSolidCube(2.0);
    glPopMatrix();

    //Simbolo Gru - Traco circulo (preto)
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(4.3, -44.5, 51.0);
        glScaled(4.0, 0.5, 0.0);
        glutSolidCube(2.0);
    glPopMatrix();


    //Parte do bolsinho - tras
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(0.0, -30.0, -39.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(1.7, 0.4, 2.0);
        glutSolidCylinder(20.0, 10.0, 50, 50);
    glPopMatrix();


    //alca da roupinha - direita
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(35.7, -30.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glRotated(30.0, 1.0, 0.0, 0.0);
        glScaled(2.3, 1.0, 1.0);
        glutSolidTorus(2.0, 20.0, 100, 100);
    glPopMatrix();

    //botao roupa - direita
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(30.0, -33.0, 50.0);
        glScaled(0.2, 0.2, 0.2);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //alca da roupinha - esquerda
     glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(-35.7, -30.0, 0.0);
        glRotated(90, 0.0, 1.0, 0.0);
        glRotated(-30.0, 1.0, 0.0, 0.0);
        glScaled(2.3, 1.0, 1.0);
        glutSolidTorus(2.0, 20.0, 100, 100);
    glPopMatrix();

    //Botao da roupa - esquerda
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-30.0, -33.0, 50.0);
        glScaled(0.2, 0.2, 0.2);
        glutSolidSphere(20, 50, 50);
    glPopMatrix();

    //Braço bolinha esquerda
glPushMatrix(); //PARA MEXER TUDO
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -30.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //PARA MEXER BRACO CIMA
glTranslated(-50.0, -30.0, 0.0);
glRotated(angulo_dir_minion1_braco_cima, 1.0, 0.0, 0.0);
glTranslated(50.0, 30.0, 0.0);
//braço longo cima
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -30.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(8.0, 20.0, 100, 100);
    glPopMatrix();

//bolinha cotovelo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(50.0, -50.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //PARA MEXER BRACO BAIXO
glTranslated(-50.0, -50.0, 0.0);
glRotated(angulo_dir_minion1_braco_baixo, 1.0, 0.0, 0.0);
glTranslated(50.0, 50.0, 0.0);
//reto bracinho baixo
    glPushMatrix(); //PARA MEXER MAO
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslated(50.0, -50.0, 0.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 15.0, 100, 100);
        glPopMatrix();

//Luvinha borda
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidTorus(2.0, 8.0, 100, 100);
        glPopMatrix();

//luvinha pulso
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 6.0, 100, 100);
        glPopMatrix();

//Palma da mao
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(50.0, -59.0, 18.0);
            glutSolidSphere(7.0, 100, 100);
        glPopMatrix();

//dedo 1
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(40.0, -55.0, 15.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 2
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(55.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 3
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(46.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();
    glPopMatrix(); //PARA MEXER MAO
    glPopMatrix(); //PARA MEXER BRACO BAIXO
    glPopMatrix(); //PARA MEXER BRACO CIMA
glPopMatrix(); //PARA MEXER TUDO

//Braço bolinha esquerda
glPushMatrix(); //PARA MEXER TUDO
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -30.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix();// PARA MEXER O BRACO CIMA
    glTranslated(-50.0, -30.0, 0.0);
    glRotated(angulo_esq_minion1_braco_cima, 1.0, 0.0, 0.0);
    glTranslated(50.0, 30.0, 0.0);
    //braço longo cima
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -30.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(8.0, 20.0, 100, 100);
    glPopMatrix();

//bolinha cotovelo
    glPushMatrix();
        glColor3f(1.0, 1.0, 0.0);
        glTranslated(-50.0, -50.0, 0.0);
        glutSolidSphere(8.0, 100, 100);
    glPopMatrix();

glPushMatrix(); //PARA MEXER BRACO BAIXO
glTranslated(-50.0, -50.0, 0.0);
glRotated(angulo_esq_minion1_braco_baixo, 1.0, 0.0, 0.0);
glTranslated(50.0, 50.0, 0.0);
//reto bracinho baixo
    glPushMatrix(); //PARA MEXER MAO
        glPushMatrix();
            glColor3f(1.0, 1.0, 0.0);
            glTranslated(-50.0, -50.0, 0.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 15.0, 100, 100);
        glPopMatrix();

//Luvinha borda
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidTorus(2.0, 8.0, 100, 100);
        glPopMatrix();

//luvinha pulso
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -57.0, 12.0);
            glRotated(30, 1.0, 0.0, 0.0);
            glutSolidCylinder(8.0, 6.0, 100, 100);
        glPopMatrix();

//Palma da mao
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-50.0, -59.0, 18.0);
            glutSolidSphere(7.0, 100, 100);
        glPopMatrix();

//dedo 1
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-40.0, -55.0, 15.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 2
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-55.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();

//dedo 3
        glPushMatrix();
            glColor3f(0.0, 0.0, 0.0);
            glTranslated(-46.0, -60.0, 22.0);
            glutSolidSphere(5.0, 100, 100);
        glPopMatrix();
    glPopMatrix(); //PARA MEXER MAO
glPopMatrix(); //PARA MEXER BRACO BAIXO
glPopMatrix(); //PARA MEXER BRACO CIMA
glPopMatrix(); //PARA MEXER TUDO


    //Perna direita

    glPushMatrix();
    glRotated(angulo_dir_minion1, 1.0, 0.0, 0.0);
        glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(-15.0, -80.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(10.0, 28.0, 100, 100);
        glPopMatrix();

        //Sapato esquerdo - base
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15.0, -115.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato esquerdo - calcanhar
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15, -105.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

     //Sapato esquerdo - bolinha da frente
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(-15.0, -115.0, 17.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    glPopMatrix();

    //Perna esquerda
    glPushMatrix();
    glRotated(angulo_esq_minion1, 1.0, 0.0, 0.0);
    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glTranslated(15.0, -80.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(10.0, 28.0, 100, 100);
    glPopMatrix();

        //Sapato direito - base
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15.0, -115.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato direito - calcanhar
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15, -105.0, 0.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glutSolidCylinder(7.0, 15.0, 100, 100);
    glPopMatrix();

    //Sapato direito - bolinha da frente
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(15.0, -115.0, 17.0);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();
    glPopMatrix();


    //Olho esquerdo - bolinha branca
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(-14.0, 10.0, 40);
        glutSolidSphere(14.0, 100, 100);
    glPopMatrix();

    //Bolinha esquerda marrom escura do olho
    glPushMatrix();
        glColor3f(0.3, 0.2, 0.1);
        glTranslated(-14.0, 10.5, 50);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    //Olho direito - bolinha branca
    glPushMatrix();
        glColor3f(1.0, 1.0, 1.0);
        glTranslated(14.0, 10.0, 40);
        glutSolidSphere(14.0, 100, 100);
    glPopMatrix();

     //Bolinha direita marrom escura do olho
    glPushMatrix();
        glColor3f(0.3, 0.2, 0.1);
        glTranslated(14.0, 10.5, 50);
        glutSolidSphere(6.0, 100, 100);
    glPopMatrix();

    //Oculos lado direito
    glPushMatrix();
        glColor3f(0.6, 0.6, 0.5);
        glTranslated(15.0, 10.0, 40.0);
        glScaled(1.5, 1.5, 5.0);
        glutSolidTorus(1.5, 10.0, 100, 100);
    glPopMatrix();

    //Oculos lado esquerdo
    glPushMatrix();
        glColor3f(0.6, 0.6, 0.5);
        glTranslated(-15.0, 10.0, 40.0);
        glScaled(1.5, 1.5, 5.0);
        glutSolidTorus(1.5, 10.0, 100, 100);
    glPopMatrix();

    //Elastico do oculos
    glPushMatrix();
        glColor3f(0.0, 0.0, 0.0);
        glTranslated(0.0, 10.0, -1.0);
        glRotated(90, 1.0, 0.0, 0.0);
        glScaled(4.5, 4.5, 4.5);
        glutSolidTorus(0.5, 10.0, 100, 100);
    glPopMatrix();

//Boca
glPushMatrix();
    glColor3f(0.0, 0.0, 0.0);
    glTranslated(0.0, -14.0, 46.8);
    glRotated(20, 0.0, 1.0, 0.0);
    glRotated(220.0, 1.0, 0.0, 0.0);
    //glScaled(1.0, 0.0, 0.0);
    draw_generic_forearm();
glPopMatrix();

glPopMatrix();

}

void casaVizinho(){
//CASA DO VIZINHO
glPushMatrix();
    glTranslated(0.0, 0.0, -50);
//fundo da casa
glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(80.0, 20.0, -140.0);
    glScaled(10.0, 11.0, 3.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(-110.0, 20.0, -140.0);
    glScaled(10.0, 11.0, 3.0);
    glutSolidCube(20);
glPopMatrix();

//telhado dos fundos
//direito
glPushMatrix();
    glColor3f(0.8, 0.2, 0.0);
    glTranslated(90.0, 170.0, -150.0);
    glScaled(6.0, 6.0, 3.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.2, 0.0);
    glTranslated(162.0, 118.0, -150.0);
    glScaled(3.0, 6.0, 0.1);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(180, 0.0, 1.0, 0.0);
    glutSolidCone(20, 20, 50, 50);
glPopMatrix();

//esquerdo
glPushMatrix();
    glColor3f(0.8, 0.2, 0.0);
    glTranslated(-80.0, 170.0, -150.0);
    glScaled(10.0, 6.0, 2.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.2, 0.0);
    glTranslated(-189.0, 117.0, -150.0);
    glScaled(3.0, 6.0, 0.1);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(180, 0.0, 1.0, 0.0);
    glutSolidCone(20, 20, 50, 50);
glPopMatrix();

//Janelas
//Esquerda
//Vidro
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(-160.0, 165.0, -115.0);
    glScaled(1.0, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-170.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-150.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 200.0,-110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 205.0, -110.0);
    glScaled(1.3, 0.4, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 130.0, -110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 125.0, -110.0);
    glScaled(1.3, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 165.0, -110.0);
    glScaled(0.1, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 180.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 160.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-160.0, 145.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//janela direita
//Vidro
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(-120.0, 165.0, -115.0);
    glScaled(1.0, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-130.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-110.0, 165.0, -110.0);
    glScaled(0.2, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 200.0, -110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 205.0, -110.0);
    glScaled(1.3, 0.4, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 130.0, -110.0);
    glScaled(1.5, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 125.0, -110.0);
    glScaled(1.3, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 165.0, -110.0);
    glScaled(0.1, 3.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 180.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 160.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-120.0, 145.0, -110.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//lado esquerdo
//parte reta
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-150.0, -20.0, -110.0);
    glScaled(3.0, 7.0, 0.1);
    glutSolidCube(20);
glPopMatrix();


//janela fundo direita
//Vidro
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(140.0, 0.0, -108.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(155.0, 0.0, -105.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(125.0, 0.0, -105.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, 50.0, -105.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, 55.0, -105.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, -50.0, -105.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, -58.0, -105.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, 0.0, -105.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, 30.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(140.0, 8.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, -14.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.2, 0.1, 0.0);
    glTranslated(140.0, -36.0, -105.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//frente
glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(-47.0, 60.0, -150.0);
    glScaled(10.0, 10.0, 10.0);
    glutSolidCube(10);
glPopMatrix();

glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(47.0, 60.0, -150.0);
    glScaled(10, 10, 10);
    glutSolidCube(10);
glPopMatrix();

glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(-50.0, -40.0, -150.0);
    glScaled(10, 10, 10);
    glutSolidCube(10);
glPopMatrix();

glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(50.0, -40.0, -150.0);
    glScaled(10, 10, 10);
    glutSolidCube(10);
glPopMatrix();

//triangulo do telhado
glPushMatrix();
    glColor3f(1.0, 0.9, 0.8);
    glTranslated(0.0, 110.0, -135.0);
    glScaled(10, 9, 6);
    glRotated(90, 1.0, 0.0, 0.0);
    glRotated(180, 0.0, 1.0, 0.0);
    glutSolidCone(10, 20, 50, 50);
glPopMatrix();

//janela de bolinha
//bolinha
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(0.0, 225.0, -100.0);
    glScaled(1.0, 1.0, 0.0);
    glutSolidSphere(20.0, 50, 50);
glPopMatrix();

//tracos
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 221.0, -90.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 221.0, -90.0);
    glRotated(90, 0.0, 0.0, 1.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 221.0, -90.0);
    glRotated(45, 0.0, 0.0, 1.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 221.0, -90.0);
    glRotated(135, 0.0, 0.0, 1.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura telhado - esquerda
glPushMatrix();
    glColor3f(0.8, 0.2, 0.0);
    glTranslated(-60.0, 185.0, -110.0);
    glRotated(60.0, 0.0, 0.0, 1.0);
    glScaled(12.0, 0.5, 3.0);
    glutSolidCube(20);
glPopMatrix();

//direita
glPushMatrix();
    glColor3f(0.8, 0.2, 0.0);
    glTranslated(60.0, 185.0, -110.0);
    glRotated(-60.0, 0.0, 0.0, 1.0);
    glScaled(12.0, 0.5, 3.0);
    glutSolidCube(20);
glPopMatrix();

//Porta da frente
glPushMatrix();
    glColor3f(0.6, 0.0, 0.0);
    glTranslated(0.0, -30.0, -95.0);
    glScaled(3.0, 6.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Detalhes da porta
//Superior esquerdo
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-22.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-3.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, 19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, -19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Superior direito
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(22.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(3.0, 0.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, 19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, -19.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Inferior esquerdo
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-22.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-3.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, -31.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(-12.0, -69.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Inferior direito
glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(22.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(3.0, -50.0, -92.0);
    glScaled(0.1, 2.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, -31.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.8, 0.0, 0.0);
    glTranslated(12.0, -69.0, -92.0);
    glScaled(1.0, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Maçaneta
glPushMatrix();
    glColor3f(0.8, 0.8, 0.8);
    glTranslated(-27.0, -25.0, -95.0);
    glScaled(0.2, 0.5, 0.1);
    glutSolidCube(20);
glPopMatrix();

//Escadas
//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, -90.0, -98.0);
    glScaled(3.0, 0.8, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, -100.0, -105.0);
    glScaled(3.0, 0.8, 0.8);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, -110.0, -100.0);
    glScaled(3.0, 0.8, 0.5);
    glutSolidCube(20);
glPopMatrix();


//Janela Direita
//Vidro
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(65.0, 0.0, -95.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(50.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-82.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, 50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, 55.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, -50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, -58.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, 0.0, -90.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, 30.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, 8.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, -14.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, -36.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Janela esquerda
//Vidro
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(-66.0, 0.0, -95.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura da janela
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-50.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(80.0, 0.0, -90.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, 50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, 55.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, -50.0, -90.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(65.0, -55.0, -90.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, 0.0, -90.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, 30.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, 8.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, -14.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-65.0, -36.0, -90.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Janela segundo andar
//Vidro
glPushMatrix();
    glColor3f(0.5, 0.8, 0.8);
    glTranslated(0.0, 130.0, -75.0);
    glScaled(1.5, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Moldura janela
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(15.0, 130.0, -70.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(-15.0, 130.0, -70.0);
    glScaled(0.2, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//Parte de cima
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 180.0, -80.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 185.0, -80.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//Parte de baixo
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 85.0, -75.0);
    glScaled(2.0, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 80.0, -80.0);
    glScaled(1.7, 0.5, 0.5);
    glutSolidCube(20);
glPopMatrix();

//linha vertical
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 135.0, -74.0);
    glScaled(0.1, 5.0, 0.0);
    glutSolidCube(20);
glPopMatrix();

//linhas horizontais
glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 100.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 120.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 140.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();

glPushMatrix();
    glColor3f(0.6, 0.4, 0.2);
    glTranslated(0.0, 160.0, -74.0);
    glScaled(1.5, 0.1, 0.0);
    glutSolidCube(20);
glPopMatrix();
glPopMatrix();
}

void Arvore(){
    glPushMatrix(); //Para toda a arvore

    //TRONCO
        glPushMatrix();
            glColor3f(0.6, 0.4, 0.2);
            glTranslated(0.0, 2.0, 0.0);
            glRotated(90, 1.0, 0.0, 0.0);
            glutSolidCylinder(0.2, 3.0, 100, 100);
        glPopMatrix();

    //TOPO
        glPushMatrix();
            glColor3f(0.0, 0.6, 0.0);
            glTranslated(0.0, 1.5, 0.0);
            glScaled(0.6, 0.6, 0.6);
            glutSolidDodecahedron();
        glPopMatrix();
    glPopMatrix(); //Para toda a arvore
}

void Arbusto(){
    glPushMatrix();
        glColor3f(0.0, 0.6, 0.0);
        glScaled(0.3, 0.3, 0.3);
        glutSolidDodecahedron();
    glPopMatrix();
}

void Presente(){

    glPushMatrix();
        glColor3f(1.0, 0.0, 0.0);
        glutSolidCube(1.0);
    glPopMatrix();
}

void mouse(int btn, int state, int x, int y){
     mouseCoords.x = x - 600/2;
     mouseCoords.y = -y + 600/2;
}


void move(){
     dis.x = mouseCoords.x - pos.x;
     dis.y = mouseCoords.y - pos.y;

     // Se a magnitude for menor que a velocidade, defina as mouseCoords
     if(sqrt(dis.y*dis.y + dis.x*dis.x) < speed){
          pos.x = mouseCoords.x;
          pos.y = mouseCoords.y;
     }
     else{
          radian = atan2(dis.y, dis.x);
          pos.x += cos(radian) * speed;
          pos.y += sin(radian) * speed;
          rot = radian * 100 / 3.14;
     }

}

void update(int value){
     move();
     glutPostRedisplay();
     //glutTimerFunc(10, update, 0);
}


void timerFunc(int value){
    //PERNA DIREITA
    if(angulo_dir_minion1 == 10 || angulo_dir_minion1 ==-10){
		ang_step_minion1_pe = -ang_step_minion1_pe;}

    angulo_dir_minion1 += ang_step_minion1_pe;

    //PERNA ESQUERDA
    if(angulo_esq_minion1 == 10 || angulo_esq_minion1 == -10){
        ang_step_minion1_pe = ang_step_minion1_pe;
    }

    angulo_esq_minion1 -= ang_step_minion1_pe;

    //BRACO ESQUERDO CIMA
    if(angulo_esq_minion1_braco_cima == 25 || angulo_esq_minion1_braco_cima == -45){
        ang_step_minion1_braco_cima = -ang_step_minion1_braco_cima;
    }

    angulo_esq_minion1_braco_cima += ang_step_minion1_braco_cima;

    //BRACO DIREITO CIMA
    if(angulo_dir_minion1_braco_cima == 25 || angulo_dir_minion1_braco_cima == -45){
        ang_step_minion1_braco_cima = ang_step_minion1_braco_cima;
    }

    angulo_dir_minion1_braco_cima -= ang_step_minion1_braco_cima;

    //BRACO ESQUERDO BAIXO
    if(angulo_esq_minion1_braco_baixo == 60 || angulo_esq_minion1_braco_baixo == -50){
        ang_step_minion1_braco_baixo = -ang_step_minion1_braco_baixo;
    }

    angulo_esq_minion1_braco_baixo += ang_step_minion1_braco_baixo;

    //BRACO DIREITO BAIXO
    if(angulo_dir_minion1_braco_baixo == 60 || angulo_dir_minion1_braco_baixo == -50){
        ang_step_minion1_braco_baixo = ang_step_minion1_braco_baixo;
    }

    angulo_dir_minion1_braco_baixo -= ang_step_minion1_braco_baixo;

    // Redesenha a cena com as novas coordenadas

	glutPostRedisplay();
	glutTimerFunc(10,timerFunc, 1);
}

void SetupRC(void){
     glClearColor(0.0, 0.8, 0.9, 0.0);
	//GLfloat luzAmbiente[4]={0.2,0.2,0.2,1.0};
	GLfloat luzAmbiente[4]={0.5,0.5,0.5,1.0};
	GLfloat luzDifusa[4]={0.7,0.7,0.7,1.0};		 /* "cor" */
	GLfloat luzEspecular[4]={1.0, 1.0, 1.0, 1.0}; /* "brilho" */
	GLfloat posicaoLuz[4]={0.0, 900.0, -3000.0, 200.0};

    GLfloat objeto_ambiente[4] = {0.5,0.0,0.0,1.0};
    GLfloat objeto_difusa[4] = {1.0,0.0,0.0,1.0};
	/* Capacidade de brilho do material */
	GLfloat especularidade[4]={0.4,0.4,0.4,0.4};
	GLint especMaterial = 50;

 	/* Especifica que a cor de fundo da janela será preta */
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	/* Ativa o uso da luz ambiente */
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, luzAmbiente);

	/* Define os parâmetros da luz de número 0 */
	glLightfv(GL_LIGHT0, GL_AMBIENT, luzAmbiente);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, luzDifusa );
	glLightfv(GL_LIGHT0, GL_SPECULAR, luzEspecular );
	glLightfv(GL_LIGHT0, GL_POSITION, posicaoLuz );

    /*glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 2.0);
    glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 1.0);
    glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.5);*/

   /* define as propriedades do material */

    glMaterialfv (GL_FRONT_AND_BACK, GL_AMBIENT, objeto_ambiente);
    glMaterialfv (GL_FRONT_AND_BACK, GL_DIFFUSE, objeto_difusa);
   /* Define a refletncia do material */
	glMaterialfv(GL_FRONT,GL_SPECULAR, especularidade);
	/* Define a concentrao do brilho */
	glMateriali(GL_FRONT,GL_SHININESS,especMaterial);

	/* Habilita a definio da cor do material a partir da cor corrente */
	glEnable(GL_COLOR_MATERIAL);
	/* Habilita o uso de iluminação*/
	glEnable(GL_LIGHTING);
	/* Habilita a luz de número 0 */
	glEnable(GL_LIGHT0);
	/* Habilita o depth-buffering */
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_FLAT);

}

void RenderScene(void){
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    glClearColor(0.0, 0.8, 0.9, 0.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-win+panX, win+panX, -win+panY, win+panY, -win, win);
    gluLookAt(0.0, 3.0, 2.0, 0.0, -2.0, -10.0, 0.0, 4.0, 2.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

	//glColor3f(0.0f, 0.0f, 1.0f);
	glPushMatrix();
        glScaled(1.3, 1.3, 1.3);
        glRotated(angx, 1.0, 0.0, 0.0);
        glRotated(angy, 0.0, 1.0, 0.0);
        glRotated(angz, 0.0, 0.0, 1.0);

        //Arbustos por Sweep
        int i;
        glPushMatrix();
        glTranslated(-5.3, 0.0, 0.0);
        for(i=0;i<10;i++){
            //Arbusto
            glPushMatrix();
                glTranslated(1.2*i, -0.5, 4.0);
                //Arbusto();
            glPopMatrix();
        }
        glPopMatrix();

        //Presente();

        //Arvore esquerda tras
        glPushMatrix();
            glTranslated(-6.5, 0.0, 0.0);
            //Arvore();
        glPopMatrix();

        //Arvore esquerda frente
        glPushMatrix();
            glTranslated(-6.5, 0.0, 3.0);
            //Arvore();
        glPopMatrix();

        //Arvore direita tras
        glPushMatrix();
            glTranslated(6.5, 0.0, 0.0);
            //Arvore();
        glPopMatrix();

        //Arvore direita frente
        glPushMatrix();
            glTranslated(6.5, 0.0, 3.0);
            //Arvore();
        glPopMatrix();


    glScaled(0.01, 0.01, 0.01);

    glPushMatrix();
        //glTranslated(pos.x, pos.y, 0);

        glTranslated(passoRL, 0.0, passoUD);
        glRotated(anguloRL, 0.0, 1.0, 0.0);
        glRotatef(rot, 0, 0, 1);
        //Minion1Natal();
        //Minion1();
        Minion2();
    glPopMatrix();

        fundo();

    glPushMatrix(); //Para posicionar casa do gru
        glTranslated(0.0, 0.0, -200.0);
        //casaGru();
    glPopMatrix(); //Para posicionar casa do gru

    glPushMatrix(); //Para posicionar a casa do vizinho a esquerda
        glTranslated(-450.0, 0.0, -200.0);
        //casaVizinho();
    glPopMatrix();  //Para posicionar a casa do vizinho a esquerda

     glPushMatrix(); //Para posicionar a casa do vizinho a esquerda
        glTranslated(450.0, 0.0, -200.0);
        //casaVizinho();
    glPopMatrix();  //Para posicionar a casa do vizinho a esquerda


	glPopMatrix();
	glutSwapBuffers();
}


void Viewing(void){
    glClearColor(0.0, 0.8, 0.9, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
    gluPerspective(angle, fAspect, 0.1, 500);

    /*Adicao da perspectiva*/
//    gluPerspective(angle, aspectRatio, near, far)):
    float height = 0.1 * tan((angle * 3.14/180)/2); // angle deve ser convertido em rd
    float width = height * fAspect;
    glFrustum(-width, width, -height, height, 0.1, 500);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
    gluLookAt(0, 100, 250, 0, -10, -400, 0, 800, 200);
}

void keyboard(unsigned char key, int x, int y ) {
	switch (key){

    case 'f': //esquerda
        passoRL = passoRL + 3.0;
        if(anguloRL < 90){
            anguloRL = anguloRL + 45;
            printf("%f\n", anguloRL);
        }

        else{
            anguloRL = anguloRL;
        }
        break ;

    case 's':
        passoRL = passoRL - 3.0;  //aumenta a escala
        if(anguloRL > -90){
            anguloRL = anguloRL - 45;
        }
        else if(anguloRL < -90){
            anguloRL = anguloRL + 45;
        }
        else{
            anguloRL = anguloRL;
        }

        break ;

    case 'd':
        printf("%f\n", anguloRL);
        passoUD = passoUD + 3.0;
        if(anguloRL < 0){
            anguloRL += 45;
        }
        else if(anguloRL > 0){
            anguloRL -= 45;
        }

        break ;

    case 'e':
        passoUD = passoUD - 3.0;
         printf("%f\n", anguloRL);
        if(anguloRL > -180){
            anguloRL = anguloRL - 45;
        }
        break ;

    case 'x':
        angx = angx + 10;  //aumenta a escala
        break ;

    case 'y':
        angy = angy + 10;  //diminui a escala
        break ;

    case 'z':
        angz = angz + 10;
        break;

    case 'X':
        angx = angx - 10;  //aumenta a escala
        break ;

    case 'Y':
        angy = angy - 10;  //diminui a escala
        break ;

    case 'Z':
        angz = angz - 10;
        break;
    case 27:
        exit (0);
        break;

    case 'a':
        angle = angle - 5.0;
        break;

    case 'A':
        angle = angle + 5.0;
        break;

    case 'B':
        angbracocimaesq = angbracocimaesq + 2.0;
        break;

    case 'b':
        angbracocimaesq = angbracocimaesq - 2.0;
        break;
    case 'w':
        win = win * 1.1;
        break;
    case 'W':
        win = win * 0.9;
        break;
    case 'p':
        panX += 0.1;
        break;
    case 'P':
        panX -= 0.1;
        break;
    case 'o':
        panY += 0.1;
        break;
    case 'O':
        panY -= 0.1;
        break;
	}

	glutPostRedisplay();
	//Viewing();
}

void transformacoes(int key, int x, int y){
     switch(key){
        case GLUT_KEY_UP:
           passoUD = passoUD - 3.0;
            printf("%f\n", anguloRL);
            if(anguloRL > -180){
                anguloRL = anguloRL - 45;
            }
           break;

        case GLUT_KEY_DOWN:
            passoUD = passoUD + 3.0;
            if(anguloRL < 0){
                anguloRL += 45;
            }
            else if(anguloRL > 0){
                anguloRL -= 45;
            }
           break;

        case GLUT_KEY_LEFT:
           passoRL = passoRL - 3.0;  //aumenta a escala
            if(anguloRL > -90){
                anguloRL = anguloRL - 45;
            }
            else if(anguloRL < -90){
                anguloRL = anguloRL + 45;
            }
            else{
                anguloRL = anguloRL;
            }
           break;

        case GLUT_KEY_RIGHT:
           passoRL = passoRL + 3.0;
            if(anguloRL < 90){
                anguloRL = anguloRL + 45;
            }
            else{
                anguloRL = anguloRL;
            }
           break;

        default:
           break;
     }
     glutPostRedisplay() ;
}

void ChangeSize(GLsizei w, GLsizei h)	{
	/* Para previnir uma divisão por zero */
	if (h == 0)
		h = 1;
    glViewport(0, 0, w, h);

	/* Calcula a correção de aspecto */
	fAspect = (GLfloat)w/(GLfloat)h;
	//Viewing();
}


int main(int argc, char** argv){
    glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(600, 600);
	glClearColor(0.0, 0.8, 0.9, 0.0);
	glutCreateWindow("Minions!");
	glutDisplayFunc(RenderScene);
    glutReshapeFunc(ChangeSize);
    glutMouseFunc(mouse);
	glutTimerFunc(10,timerFunc,0);
	glutTimerFunc(25, update, 0);
    glutKeyboardFunc(keyboard);
     glutSpecialFunc(transformacoes);
	SetupRC();
	glutMainLoop();
}
