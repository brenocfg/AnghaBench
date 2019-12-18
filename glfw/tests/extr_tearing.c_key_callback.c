#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  refreshRate; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
#define  GLFW_KEY_DOWN 132 
#define  GLFW_KEY_ENTER 131 
#define  GLFW_KEY_ESCAPE 130 
#define  GLFW_KEY_F11 129 
#define  GLFW_KEY_UP 128 
 int GLFW_MOD_ALT ; 
 int GLFW_PRESS ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  glfwSetWindowMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  set_swap_interval (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_interval ; 
 int /*<<< orphan*/  swap_tear ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_UP:
        {
            if (swap_interval + 1 > swap_interval)
                set_swap_interval(window, swap_interval + 1);
            break;
        }

        case GLFW_KEY_DOWN:
        {
            if (swap_tear)
            {
                if (swap_interval - 1 < swap_interval)
                    set_swap_interval(window, swap_interval - 1);
            }
            else
            {
                if (swap_interval - 1 >= 0)
                    set_swap_interval(window, swap_interval - 1);
            }
            break;
        }

        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, 1);
            break;

        case GLFW_KEY_F11:
        case GLFW_KEY_ENTER:
        {
            static int x, y, width, height;

            if (mods != GLFW_MOD_ALT)
                return;

            if (glfwGetWindowMonitor(window))
                glfwSetWindowMonitor(window, NULL, x, y, width, height, 0);
            else
            {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                glfwGetWindowPos(window, &x, &y);
                glfwGetWindowSize(window, &width, &height);
                glfwSetWindowMonitor(window, monitor,
                                     0, 0, mode->width, mode->height,
                                     mode->refreshRate);
            }

            break;
        }
    }
}