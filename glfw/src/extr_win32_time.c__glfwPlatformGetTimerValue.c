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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ hasPC; } ;
struct TYPE_5__ {TYPE_1__ win32; } ;
struct TYPE_6__ {TYPE_2__ timer; } ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  QueryPerformanceCounter (int /*<<< orphan*/ *) ; 
 TYPE_3__ _glfw ; 
 int /*<<< orphan*/  timeGetTime () ; 

uint64_t _glfwPlatformGetTimerValue(void)
{
    if (_glfw.timer.win32.hasPC)
    {
        uint64_t value;
        QueryPerformanceCounter((LARGE_INTEGER*) &value);
        return value;
    }
    else
        return (uint64_t) timeGetTime();
}