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
struct TYPE_4__ {int /*<<< orphan*/  (* key ) (int /*<<< orphan*/ *,int,int,int,int) ;} ;
struct TYPE_5__ {int* keys; TYPE_1__ callbacks; int /*<<< orphan*/  lockKeyMods; scalar_t__ stickyKeys; } ;
typedef  TYPE_2__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int GLFW_KEY_LAST ; 
 int GLFW_MOD_CAPS_LOCK ; 
 int GLFW_MOD_NUM_LOCK ; 
 int GLFW_PRESS ; 
 int GLFW_RELEASE ; 
 int GLFW_REPEAT ; 
 scalar_t__ GLFW_TRUE ; 
 int _GLFW_STICK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int,int,int,int) ; 

void _glfwInputKey(_GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key >= 0 && key <= GLFW_KEY_LAST)
    {
        GLFWbool repeated = GLFW_FALSE;

        if (action == GLFW_RELEASE && window->keys[key] == GLFW_RELEASE)
            return;

        if (action == GLFW_PRESS && window->keys[key] == GLFW_PRESS)
            repeated = GLFW_TRUE;

        if (action == GLFW_RELEASE && window->stickyKeys)
            window->keys[key] = _GLFW_STICK;
        else
            window->keys[key] = (char) action;

        if (repeated)
            action = GLFW_REPEAT;
    }

    if (!window->lockKeyMods)
        mods &= ~(GLFW_MOD_CAPS_LOCK | GLFW_MOD_NUM_LOCK);

    if (window->callbacks.key)
        window->callbacks.key((GLFWwindow*) window, key, scancode, action, mods);
}