#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int autoIconify; int resizable; int decorated; int floating; int focusOnShow; int /*<<< orphan*/  monitor; } ;
typedef  TYPE_1__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int GLFW_AUTO_ICONIFY ; 
 int GLFW_DECORATED ; 
 int GLFW_FALSE ; 
 int GLFW_FLOATING ; 
 int GLFW_FOCUS_ON_SHOW ; 
 int /*<<< orphan*/  GLFW_INVALID_ENUM ; 
 int GLFW_RESIZABLE ; 
 int GLFW_TRUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowDecorated (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowFloating (TYPE_1__*,int) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowResizable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void glfwSetWindowAttrib(GLFWwindow* handle, int attrib, int value)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    _GLFW_REQUIRE_INIT();

    value = value ? GLFW_TRUE : GLFW_FALSE;

    if (attrib == GLFW_AUTO_ICONIFY)
        window->autoIconify = value;
    else if (attrib == GLFW_RESIZABLE)
    {
        if (window->resizable == value)
            return;

        window->resizable = value;
        if (!window->monitor)
            _glfwPlatformSetWindowResizable(window, value);
    }
    else if (attrib == GLFW_DECORATED)
    {
        if (window->decorated == value)
            return;

        window->decorated = value;
        if (!window->monitor)
            _glfwPlatformSetWindowDecorated(window, value);
    }
    else if (attrib == GLFW_FLOATING)
    {
        if (window->floating == value)
            return;

        window->floating = value;
        if (!window->monitor)
            _glfwPlatformSetWindowFloating(window, value);
    }
    else if (attrib == GLFW_FOCUS_ON_SHOW)
        window->focusOnShow = value;
    else
        _glfwInputError(GLFW_INVALID_ENUM, "Invalid window attribute 0x%08X", attrib);
}