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
struct TYPE_3__ {scalar_t__ offset; } ;
struct TYPE_4__ {TYPE_1__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  _GLFW_REQUIRE_INIT_OR_RETURN (double) ; 
 TYPE_2__ _glfw ; 
 double _glfwPlatformGetTimerFrequency () ; 
 scalar_t__ _glfwPlatformGetTimerValue () ; 

double glfwGetTime(void)
{
    _GLFW_REQUIRE_INIT_OR_RETURN(0.0);
    return (double) (_glfwPlatformGetTimerValue() - _glfw.timer.offset) /
        _glfwPlatformGetTimerFrequency();
}