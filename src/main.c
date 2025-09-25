#include <GL/glut.h>
#include "car.h"
#include "track.h"
#include "camera.h"
#include "utils.h"

// --- Funções locais (callbacks) ---
void display(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // 1. Atualiza câmera
    updateCamera(&car);

    // 2. Desenha pista
    drawOvalTrack();

    // 3. Desenha carro
    drawCar();

    // 4. HUD ou informações na tela
    drawHUD();

    glutSwapBuffers();
}

void reshape(int width, int height) {
    if (height == 0) height = 1;
    float aspect = (float)width / (float)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, aspect, 0.1, 200.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void keyboardDown(unsigned char key, int x, int y) {
    handleKeyDown(key);
}

void keyboardUp(unsigned char key, int x, int y) {
    handleKeyUp(key);
}

void timerFunc(int value) {
    float dt = getDeltaTime();
    updateCarPhysics(dt); // Física do carro
    glutPostRedisplay();
    glutTimerFunc(16, timerFunc, 0);
}

// --- Função principal ---
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(1024, 768);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Carro 3D - Pista Oval");

    initScene(); // Inicialização de luzes, materiais e variáveis

    // --- Registra callbacks ---
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);
    glutTimerFunc(16, timerFunc, 0);

    glutMainLoop();
    return 0;
}
