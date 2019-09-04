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
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwPlatformGetWindowContentScale (int /*<<< orphan*/ *,float*,float*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void glfwGetWindowContentScale(GLFWwindow* handle,
                                       float* xscale, float* yscale)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);

    if (xscale)
        *xscale = 0.f;
    if (yscale)
        *yscale = 0.f;

    _GLFW_REQUIRE_INIT();
    _glfwPlatformGetWindowContentScale(window, xscale, yscale);
}