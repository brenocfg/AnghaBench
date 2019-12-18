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
struct TYPE_3__ {int /*<<< orphan*/  refreshRate; int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  TYPE_1__ GLFWvidmode ;
typedef  int /*<<< orphan*/  GLFWmonitor ;

/* Variables and functions */
 int GLFW_KEY_ENTER ; 
 int GLFW_KEY_ESCAPE ; 
 int GLFW_KEY_F11 ; 
 int GLFW_MOD_ALT ; 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 scalar_t__ glfwGetWindowMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetWindowMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  windowed_height ; 
 int /*<<< orphan*/  windowed_width ; 
 int /*<<< orphan*/  windowed_xpos ; 
 int /*<<< orphan*/  windowed_ypos ; 

void key_callback( GLFWwindow* window, int key, int scancode, int action, int mods )
{
    if (action != GLFW_PRESS)
        return;

    if (key == GLFW_KEY_ESCAPE && mods == 0)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    if ((key == GLFW_KEY_ENTER && mods == GLFW_MOD_ALT) ||
        (key == GLFW_KEY_F11 && mods == GLFW_MOD_ALT))
    {
        if (glfwGetWindowMonitor(window))
        {
            glfwSetWindowMonitor(window, NULL,
                                 windowed_xpos, windowed_ypos,
                                 windowed_width, windowed_height, 0);
        }
        else
        {
            GLFWmonitor* monitor = glfwGetPrimaryMonitor();
            if (monitor)
            {
                const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                glfwGetWindowPos(window, &windowed_xpos, &windowed_ypos);
                glfwGetWindowSize(window, &windowed_width, &windowed_height);
                glfwSetWindowMonitor(window, monitor, 0, 0, mode->width, mode->height, mode->refreshRate);
            }
        }
    }
}