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
 double MAX_DELTA_T ; 
 int /*<<< orphan*/  adjust_grid () ; 
 int /*<<< orphan*/  calc_grid () ; 
 int /*<<< orphan*/  cursor_position_callback ; 
 int /*<<< orphan*/  draw_scene (int /*<<< orphan*/ *) ; 
 double dt ; 
 int /*<<< orphan*/  error_callback ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  framebuffer_size_callback (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  gladLoadGL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * glfwCreateWindow (int,int,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetFramebufferSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetProcAddress ; 
 double glfwGetTime () ; 
 int /*<<< orphan*/  glfwInit () ; 
 int /*<<< orphan*/  glfwMakeContextCurrent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwPollEvents () ; 
 int /*<<< orphan*/  glfwSetCursorPosCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetErrorCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetFramebufferSizeCallback (int /*<<< orphan*/ *,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int,int)) ; 
 int /*<<< orphan*/  glfwSetKeyCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetMouseButtonCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetScrollCallback (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSwapInterval (int) ; 
 int /*<<< orphan*/  glfwTerminate () ; 
 int /*<<< orphan*/  glfwWindowShouldClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_grid () ; 
 int /*<<< orphan*/  init_opengl () ; 
 int /*<<< orphan*/  init_vertices () ; 
 int /*<<< orphan*/  key_callback ; 
 int /*<<< orphan*/  mouse_button_callback ; 
 int /*<<< orphan*/  scroll_callback ; 

int main(int argc, char* argv[])
{
    GLFWwindow* window;
    double t, dt_total, t_old;
    int width, height;

    glfwSetErrorCallback(error_callback);

    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(640, 480, "Wave Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }

    glfwSetKeyCallback(window, key_callback);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwMakeContextCurrent(window);
    gladLoadGL(glfwGetProcAddress);
    glfwSwapInterval(1);

    glfwGetFramebufferSize(window, &width, &height);
    framebuffer_size_callback(window, width, height);

    // Initialize OpenGL
    init_opengl();

    // Initialize simulation
    init_vertices();
    init_grid();
    adjust_grid();

    // Initialize timer
    t_old = glfwGetTime() - 0.01;

    while (!glfwWindowShouldClose(window))
    {
        t = glfwGetTime();
        dt_total = t - t_old;
        t_old = t;

        // Safety - iterate if dt_total is too large
        while (dt_total > 0.f)
        {
            // Select iteration time step
            dt = dt_total > MAX_DELTA_T ? MAX_DELTA_T : dt_total;
            dt_total -= dt;

            // Calculate wave propagation
            calc_grid();
        }

        // Compute height of each vertex
        adjust_grid();

        // Draw wave grid to OpenGL display
        draw_scene(window);

        glfwPollEvents();
    }

    glfwTerminate();
    exit(EXIT_SUCCESS);
}