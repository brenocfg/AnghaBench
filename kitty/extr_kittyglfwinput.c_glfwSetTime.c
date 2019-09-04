#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_3__ {scalar_t__ offset; } ;
struct TYPE_4__ {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_INVALID_VALUE ; 
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT () ; 
 TYPE_2__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*,double) ; 
 double _glfwPlatformGetTimerFrequency () ; 
 scalar_t__ _glfwPlatformGetTimerValue () ; 

void glfwSetTime(double time)
{
    _GLFW_REQUIRE_INIT();

    if (time != time || time < 0.0 || time > 18446744073.0)
    {
        _glfwInputError(GLFW_INVALID_VALUE, "Invalid time %f", time);
        return;
    }

    _glfw.timer.offset = _glfwPlatformGetTimerValue() -
        (uint64_t) (time * _glfwPlatformGetTimerFrequency());
}