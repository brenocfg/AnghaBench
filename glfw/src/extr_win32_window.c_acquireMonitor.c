#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_4__* monitor; int /*<<< orphan*/  videoMode; } ;
typedef  TYPE_2__ _GLFWwindow ;
struct TYPE_8__ {int /*<<< orphan*/  acquiredMonitorCount; int /*<<< orphan*/  mouseTrailSize; } ;
struct TYPE_11__ {TYPE_1__ win32; } ;
struct TYPE_10__ {int /*<<< orphan*/  window; } ;

/* Variables and functions */
 int ES_CONTINUOUS ; 
 int ES_DISPLAY_REQUIRED ; 
 scalar_t__ IsWindowsXPOrGreater () ; 
 int /*<<< orphan*/  SPI_GETMOUSETRAILS ; 
 int /*<<< orphan*/  SPI_SETMOUSETRAILS ; 
 int /*<<< orphan*/  SetThreadExecutionState (int) ; 
 int /*<<< orphan*/  SystemParametersInfo (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_7__ _glfw ; 
 int /*<<< orphan*/  _glfwInputMonitorWindow (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  _glfwSetVideoModeWin32 (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void acquireMonitor(_GLFWwindow* window)
{
    if (!_glfw.win32.acquiredMonitorCount)
    {
        SetThreadExecutionState(ES_CONTINUOUS | ES_DISPLAY_REQUIRED);

        // HACK: When mouse trails are enabled the cursor becomes invisible when
        //       the OpenGL ICD switches to page flipping
        if (IsWindowsXPOrGreater())
        {
            SystemParametersInfo(SPI_GETMOUSETRAILS, 0, &_glfw.win32.mouseTrailSize, 0);
            SystemParametersInfo(SPI_SETMOUSETRAILS, 0, 0, 0);
        }
    }

    if (!window->monitor->window)
        _glfw.win32.acquiredMonitorCount++;

    _glfwSetVideoModeWin32(window->monitor, &window->videoMode);
    _glfwInputMonitorWindow(window->monitor, window);
}