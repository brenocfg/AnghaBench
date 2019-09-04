#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int frequency; int /*<<< orphan*/  monotonic; } ;
struct TYPE_5__ {TYPE_1__ posix; } ;
struct TYPE_6__ {TYPE_2__ timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 TYPE_3__ _glfw ; 

void _glfwInitTimerPOSIX(void)
{
#if defined(CLOCK_MONOTONIC)
    struct timespec ts;

    if (clock_gettime(CLOCK_MONOTONIC, &ts) == 0)
    {
        _glfw.timer.posix.monotonic = GLFW_TRUE;
        _glfw.timer.posix.frequency = 1000000000;
    }
    else
#endif
    {
        _glfw.timer.posix.monotonic = GLFW_FALSE;
        _glfw.timer.posix.frequency = 1000000;
    }
}