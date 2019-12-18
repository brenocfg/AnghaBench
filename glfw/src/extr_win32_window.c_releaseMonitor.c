#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_4__* monitor; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_7__ {int /*<<< orphan*/  mouseTrailSize; int /*<<< orphan*/  acquiredMonitorCount; } ;
struct TYPE_10__ {TYPE_1__ win32; } ;
struct TYPE_9__ {TYPE_2__* window; } ;

/* Variables and functions */
 int /*<<< orphan*/  ES_CONTINUOUS ; 
 scalar_t__ IsWindowsXPOrGreater () ; 
 int /*<<< orphan*/  SPI_SETMOUSETRAILS ; 
 int /*<<< orphan*/  SetThreadExecutionState (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  _glfwInputMonitorWindow (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _glfwRestoreVideoModeWin32 (TYPE_4__*) ; 

__attribute__((used)) static void releaseMonitor(_GLFWwindow* window)
{
    if (window->monitor->window != window)
        return;

    _glfw.win32.acquiredMonitorCount--;
    if (!_glfw.win32.acquiredMonitorCount)
    {
        SetThreadExecutionState(ES_CONTINUOUS);

        // HACK: Restore mouse trail length saved in acquireMonitor
        if (IsWindowsXPOrGreater())
            SystemParametersInfo(SPI_SETMOUSETRAILS, _glfw.win32.mouseTrailSize, 0, 0);
    }

    _glfwInputMonitorWindow(window->monitor, NULL);
    _glfwRestoreVideoModeWin32(window->monitor);
}