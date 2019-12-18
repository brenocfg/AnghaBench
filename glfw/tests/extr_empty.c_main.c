#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  thrd_t ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glClearColor (float,float,float,float) ; 
 int /*<<< orphan*/  glViewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwDestroyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 int /*<<< orphan*/  glfwHideWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEvents () ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 float nrand () ; 
 scalar_t__ running ; 
 scalar_t__ sqrt (float) ; 
 int /*<<< orphan*/  srand (unsigned int) ; 
 int /*<<< orphan*/  stderr ; 
 scalar_t__ thrd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thrd_join (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ thrd_success ; 
 int /*<<< orphan*/  thread_main ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

int main(void)
{
    int result;
    thrd_t thread;
    GLFWwindow* window;

    srand((unsigned int) time(NULL));

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Empty Event Test", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSetKeyCallback(window, key_callback);

    if (thrd_create(&thread, thread_main, NULL) != thrd_success)
    {
        fprintf(stderr, "Failed to create secondary thread\n");

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    while (running)
    {
        int width, height;
        float r = nrand(), g = nrand(), b = nrand();
        float l = (float) sqrt(r * r + g * g + b * b);

        glfwGetFramebufferSize(window, &width, &height);

        glViewport(0, 0, width, height);
        glClearColor(r / l, g / l, b / l, 1.f);
        glClear(GL_COLOR_BUFFER_BIT);
        glfwSwapBuffers(window);

        glfwWaitEvents();

        if (glfwWindowShouldClose(window))
            running = GLFW_FALSE;
    }

    glfwHideWindow(window);
    thrd_join(thread, &result);
    glfwDestroyWindow(window);

    glfwTerminate();
    exit(EXIT_SUCCESS);
}