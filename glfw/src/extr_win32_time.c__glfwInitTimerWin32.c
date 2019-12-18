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
typedef  int uint64_t ;
struct TYPE_4__ {int frequency; int /*<<< orphan*/  hasPC; } ;
struct TYPE_5__ {TYPE_1__ win32; } ;
struct TYPE_6__ {TYPE_2__ timer; } ;
typedef  int /*<<< orphan*/  LARGE_INTEGER ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 scalar_t__ QueryPerformanceFrequency (int /*<<< orphan*/ *) ; 
 TYPE_3__ _glfw ; 

void _glfwInitTimerWin32(void)
{
    uint64_t frequency;

    if (QueryPerformanceFrequency((LARGE_INTEGER*) &frequency))
    {
        _glfw.timer.win32.hasPC = GLFW_TRUE;
        _glfw.timer.win32.frequency = frequency;
    }
    else
    {
        _glfw.timer.win32.hasPC = GLFW_FALSE;
        _glfw.timer.win32.frequency = 1000;
    }
}