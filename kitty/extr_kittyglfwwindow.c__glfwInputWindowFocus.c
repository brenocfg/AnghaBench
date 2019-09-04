#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* focus ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;} ;
struct TYPE_8__ {scalar_t__* keys; scalar_t__* mouseButtons; scalar_t__ id; TYPE_1__ callbacks; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_9__ {scalar_t__ focusedWindowId; } ;
typedef  int /*<<< orphan*/  GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int GLFW_KEY_LAST ; 
 int GLFW_MOUSE_BUTTON_LAST ; 
 scalar_t__ GLFW_PRESS ; 
 int /*<<< orphan*/  GLFW_RELEASE ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwInputKeyboard (TYPE_2__*,int,int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _glfwInputMouseClick (TYPE_2__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _glfwPlatformGetKeyScancode (int) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void _glfwInputWindowFocus(_GLFWwindow* window, GLFWbool focused)
{
    if (window->callbacks.focus)
        window->callbacks.focus((GLFWwindow*) window, focused);

    if (!focused)
    {
        int key, button;
        _glfw.focusedWindowId = 0;

        for (key = 0;  key <= GLFW_KEY_LAST;  key++)
        {
            if (window->keys[key] == GLFW_PRESS)
            {
                const int scancode = _glfwPlatformGetKeyScancode(key);
                _glfwInputKeyboard(window, key, scancode, GLFW_RELEASE, 0, "", 0);
            }
        }

        for (button = 0;  button <= GLFW_MOUSE_BUTTON_LAST;  button++)
        {
            if (window->mouseButtons[button] == GLFW_PRESS)
                _glfwInputMouseClick(window, button, GLFW_RELEASE, 0);
        }
    } else
        _glfw.focusedWindowId = window->id;
}