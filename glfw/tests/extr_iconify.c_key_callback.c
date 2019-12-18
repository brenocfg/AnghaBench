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
 int /*<<< orphan*/  GLFW_AUTO_ICONIFY ; 
 int /*<<< orphan*/  GLFW_DECORATED ; 
 int /*<<< orphan*/  GLFW_FLOATING ; 
#define  GLFW_KEY_A 137 
#define  GLFW_KEY_B 136 
#define  GLFW_KEY_D 135 
#define  GLFW_KEY_ENTER 134 
#define  GLFW_KEY_ESCAPE 133 
#define  GLFW_KEY_F 132 
#define  GLFW_KEY_F11 131 
#define  GLFW_KEY_I 130 
#define  GLFW_KEY_M 129 
#define  GLFW_KEY_R 128 
 int GLFW_MOD_ALT ; 
 int GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RESIZABLE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 int /*<<< orphan*/ * glfwGetPrimaryMonitor () ; 
 double glfwGetTime () ; 
 TYPE_1__* glfwGetVideoMode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowAttrib (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwGetWindowMonitor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowPos (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwGetWindowSize (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwIconifyWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwMaximizeWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwRestoreWindow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  glfwSetWindowAttrib (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  glfwSetWindowMonitor (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glfwSetWindowShouldClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,double,char*) ; 
 int /*<<< orphan*/  windowed_height ; 
 int /*<<< orphan*/  windowed_width ; 
 int /*<<< orphan*/  windowed_xpos ; 
 int /*<<< orphan*/  windowed_ypos ; 

__attribute__((used)) static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    printf("%0.2f Key %s\n",
           glfwGetTime(),
           action == GLFW_PRESS ? "pressed" : "released");

    if (action != GLFW_PRESS)
        return;

    switch (key)
    {
        case GLFW_KEY_I:
            glfwIconifyWindow(window);
            break;
        case GLFW_KEY_M:
            glfwMaximizeWindow(window);
            break;
        case GLFW_KEY_R:
            glfwRestoreWindow(window);
            break;
        case GLFW_KEY_ESCAPE:
            glfwSetWindowShouldClose(window, GLFW_TRUE);
            break;
        case GLFW_KEY_A:
            glfwSetWindowAttrib(window, GLFW_AUTO_ICONIFY, !glfwGetWindowAttrib(window, GLFW_AUTO_ICONIFY));
            break;
        case GLFW_KEY_B:
            glfwSetWindowAttrib(window, GLFW_RESIZABLE, !glfwGetWindowAttrib(window, GLFW_RESIZABLE));
            break;
        case GLFW_KEY_D:
            glfwSetWindowAttrib(window, GLFW_DECORATED, !glfwGetWindowAttrib(window, GLFW_DECORATED));
            break;
        case GLFW_KEY_F:
            glfwSetWindowAttrib(window, GLFW_FLOATING, !glfwGetWindowAttrib(window, GLFW_FLOATING));
            break;
        case GLFW_KEY_F11:
        case GLFW_KEY_ENTER:
        {
            if (mods != GLFW_MOD_ALT)
                return;

            if (glfwGetWindowMonitor(window))
            {
                glfwSetWindowMonitor(window, NULL,
                                     windowed_xpos, windowed_ypos,
                                     windowed_width, windowed_height,
                                     0);
            }
            else
            {
                GLFWmonitor* monitor = glfwGetPrimaryMonitor();
                if (monitor)
                {
                    const GLFWvidmode* mode = glfwGetVideoMode(monitor);
                    glfwGetWindowPos(window, &windowed_xpos, &windowed_ypos);
                    glfwGetWindowSize(window, &windowed_width, &windowed_height);
                    glfwSetWindowMonitor(window, monitor,
                                         0, 0, mode->width, mode->height,
                                         mode->refreshRate);
                }
            }

            break;
        }
    }
}