#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* mouseButton ) (int /*<<< orphan*/ *,int,int,int) ;} ;
struct TYPE_5__ {char* mouseButtons; TYPE_1__ callbacks; scalar_t__ stickyMouseButtons; int /*<<< orphan*/  lockKeyMods; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int GLFW_MOD_CAPS_LOCK ; 
 int GLFW_MOD_NUM_LOCK ; 
 int GLFW_MOUSE_BUTTON_LAST ; 
 int GLFW_RELEASE ; 
 char _GLFW_STICK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int,int) ; 

void _glfwInputMouseClick(_GLFWwindow* window, int button, int action, int mods)
{
    if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
        return;

    if (!window->lockKeyMods)
        mods &= ~(GLFW_MOD_CAPS_LOCK | GLFW_MOD_NUM_LOCK);

    if (action == GLFW_RELEASE && window->stickyMouseButtons)
        window->mouseButtons[button] = _GLFW_STICK;
    else
        window->mouseButtons[button] = (char) action;

    if (window->callbacks.mouseButton)
        window->callbacks.mouseButton((GLFWwindow*) window, button, action, mods);
}