#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  size; } ;
struct TYPE_8__ {TYPE_7__ originalRamp; } ;
typedef  TYPE_1__ _GLFWmonitor ;
struct TYPE_9__ {scalar_t__ size; int /*<<< orphan*/ * blue; int /*<<< orphan*/ * green; int /*<<< orphan*/ * red; } ;
typedef  int /*<<< orphan*/  GLFWmonitor ;
typedef  TYPE_2__ GLFWgammaramp ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  _glfwPlatformGetGammaRamp (TYPE_1__*,TYPE_7__*) ; 
 int /*<<< orphan*/  _glfwPlatformSetGammaRamp (TYPE_1__*,TYPE_2__ const*) ; 
 int /*<<< orphan*/  assert (int) ; 

void glfwSetGammaRamp(GLFWmonitor* handle, const GLFWgammaramp* ramp)
{
    _GLFWmonitor* monitor = (_GLFWmonitor*) handle;
    assert(monitor != NULL);
    assert(ramp != NULL);
    assert(ramp->size > 0);
    assert(ramp->red != NULL);
    assert(ramp->green != NULL);
    assert(ramp->blue != NULL);

    if (ramp->size <= 0)
    {
        _glfwInputError(GLFW_INVALID_VALUE,
                        "Invalid gamma ramp size %i",
                        ramp->size);
        return;
    }

    _GLFW_REQUIRE_INIT();

    if (!monitor->originalRamp.size)
    {
        if (!_glfwPlatformGetGammaRamp(monitor, &monitor->originalRamp))
            return;
    }

    _glfwPlatformSetGammaRamp(monitor, ramp);
}