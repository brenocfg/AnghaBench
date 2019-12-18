#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ redBits; scalar_t__ greenBits; scalar_t__ blueBits; scalar_t__ refreshRate; int width; scalar_t__ height; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int /*<<< orphan*/  GLFW_BLUE_BITS ; 
 int /*<<< orphan*/  GLFW_GREEN_BITS ; 
 int /*<<< orphan*/  GLFW_RED_BITS ; 
 int /*<<< orphan*/  GLFW_REFRESH_RATE ; 
 int /*<<< orphan*/  GL_BLUE_BITS ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_GREEN_BITS ; 
 int /*<<< orphan*/  GL_RED_BITS ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 char* format_mode (TYPE_1__ const*) ; 
 int /*<<< orphan*/  framebuffer_size_callback ; 
 int /*<<< orphan*/  glClear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glGetIntegerv (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,scalar_t__,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwDestroyWindow (int /*<<< orphan*/ *) ; 
 char* glfwGetMonitorName (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetPrimaryMonitor () ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 double glfwGetTime () ; 
 TYPE_1__* glfwGetVideoModes (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,scalar_t__*) ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetTime (double) ; 
 int /*<<< orphan*/  glfwSwapBuffers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowHint (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void test_modes(GLFWmonitor* monitor)
{
    int i, count;
    GLFWwindow* window;
    const GLFWvidmode* modes = glfwGetVideoModes(monitor, &count);

    for (i = 0;  i < count;  i++)
    {
        const GLFWvidmode* mode = modes + i;
        GLFWvidmode current;

        glfwWindowHint(GLFW_RED_BITS, mode->redBits);
        glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
        glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
        glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

        printf("Testing mode %u on monitor %s: %s\n",
               (unsigned int) i,
               glfwGetMonitorName(monitor),
               format_mode(mode));

        window = glfwCreateWindow(mode->width, mode->height,
                                  "Video Mode Test",
                                  glfwGetPrimaryMonitor(),
                                  NULL);
        if (!window)
        {
            printf("Failed to enter mode %u: %s\n",
                   (unsigned int) i,
                   format_mode(mode));
            continue;
        }

        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSetKeyCallback(window, key_callback);

        glfwMakeContextCurrent(window);
        gladLoadGL(glfwGetProcAddress);
        glfwSwapInterval(1);

        glfwSetTime(0.0);

        while (glfwGetTime() < 5.0)
        {
            glClear(GL_COLOR_BUFFER_BIT);
            glfwSwapBuffers(window);
            glfwPollEvents();

            if (glfwWindowShouldClose(window))
            {
                printf("User terminated program\n");

                glfwTerminate();
                exit(EXIT_SUCCESS);
            }
        }

        glGetIntegerv(GL_RED_BITS, &current.redBits);
        glGetIntegerv(GL_GREEN_BITS, &current.greenBits);
        glGetIntegerv(GL_BLUE_BITS, &current.blueBits);

        glfwGetWindowSize(window, &current.width, &current.height);

        if (current.redBits != mode->redBits ||
            current.greenBits != mode->greenBits ||
            current.blueBits != mode->blueBits)
        {
            printf("*** Color bit mismatch: (%i %i %i) instead of (%i %i %i)\n",
                   current.redBits, current.greenBits, current.blueBits,
                   mode->redBits, mode->greenBits, mode->blueBits);
        }

        if (current.width != mode->width || current.height != mode->height)
        {
            printf("*** Size mismatch: %ix%i instead of %ix%i\n",
                   current.width, current.height,
                   mode->width, mode->height);
        }

        printf("Closing window\n");

        glfwDestroyWindow(window);
        window = NULL;

        glfwPollEvents();
    }
}