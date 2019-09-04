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
struct TYPE_3__ {int numer; int denom; int /*<<< orphan*/  resizable; scalar_t__ monitor; } ;
typedef  TYPE_1__ _GLFWwindow ;
typedef  int /*<<< orphan*/  GLFWwindow ;

/* Variables and functions */
 int GLFW_DONT_CARE ; 
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  _glfwPlatformSetWindowAspectRatio (TYPE_1__*,int,int) ; 
 int /*<<< orphan*/  assert (int) ; 

void glfwSetWindowAspectRatio(GLFWwindow* handle, int numer, int denom)
{
    _GLFWwindow* window = (_GLFWwindow*) handle;
    assert(window != NULL);
    assert(numer != 0);
    assert(denom != 0);

    _GLFW_REQUIRE_INIT();

    if (numer != GLFW_DONT_CARE && denom != GLFW_DONT_CARE)
    {
        if (numer <= 0 || denom <= 0)
        {
            _glfwInputError(GLFW_INVALID_VALUE,
                            "Invalid window aspect ratio %i:%i",
                            numer, denom);
            return;
        }
    }

    window->numer = numer;
    window->denom = denom;

    if (window->monitor || !window->resizable)
        return;

    _glfwPlatformSetWindowAspectRatio(window, numer, denom);
}