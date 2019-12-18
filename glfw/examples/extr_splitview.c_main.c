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
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 scalar_t__ GLAD_GL_ARB_multisample ; 
 scalar_t__ GLAD_GL_VERSION_1_3 ; 
 int /*<<< orphan*/  GLFW_SAMPLES ; 
 int /*<<< orphan*/  GL_MULTISAMPLE_ARB ; 
 int /*<<< orphan*/  cursorPosFun ; 
 scalar_t__ do_redraw ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  framebufferSizeFun (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glEnable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetCursorPosCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowRefreshCallback (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWaitEvents () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,int) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  height ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  mouseButtonFun ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  width ; 
 int /*<<< orphan*/  windowRefreshFun (int /*<<< orphan*/ *) ; 

int main(void)
{
    GLFWwindow* window;

    // Initialise GLFW
    if (!glfwInit())
    {
        fprintf(stderr, "Failed to initialize GLFW\n");
        exit(EXIT_FAILURE);
    }

    glfwWindowHint(GLFW_SAMPLES, 4);

    // Open OpenGL window
    window = glfwCreateWindow(500, 500, "Split view demo", NULL, NULL);
    if (!window)
    {
        fprintf(stderr, "Failed to open GLFW window\n");

        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    // Set callback functions
    glfwSetFramebufferSizeCallback(window, framebufferSizeFun);
    glfwSetWindowRefreshCallback(window, windowRefreshFun);
    glfwSetCursorPosCallback(window, cursorPosFun);
    glfwSetMouseButtonCallback(window, mouseButtonFun);
    glfwSetKeyCallback(window, key_callback);

    // Enable vsync
    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    if (GLAD_GL_ARB_multisample || GLAD_GL_VERSION_1_3)
        glEnable(GL_MULTISAMPLE_ARB);

    glfwGetFramebufferSize(window, &width, &height);
    framebufferSizeFun(window, width, height);

    // Main loop
    for (;;)
    {
        // Only redraw if we need to
        if (do_redraw)
            windowRefreshFun(window);

        // Wait for new events
        glfwWaitEvents();

        // Check if the window should be closed
        if (glfwWindowShouldClose(window))
            break;
    }

    // Close OpenGL window and terminate GLFW
    glfwTerminate();

    exit(EXIT_SUCCESS);
}