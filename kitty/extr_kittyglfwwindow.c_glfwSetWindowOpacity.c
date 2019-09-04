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
typedef  int /*<<< orphan*/  _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,float) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowOpacity (int /*<<< orphan*/ *,float) ; 
 int /*<<< orphan*/  assert (int) ; 

void glfwSetWindowOpacity(GLFWwindow* handle, float opacity)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);
    assert(opacity == opacity);
    assert(opacity >= 0.f);
    assert(opacity <= 1.f);

    _GLFW_REQUIRE_INIT();

    if (opacity != opacity || opacity < 0.f || opacity > 1.f)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid window opacity %f", opacity);
        return;
    }

    _glfwPlatformSetWindowOpacity(window, opacity);
}