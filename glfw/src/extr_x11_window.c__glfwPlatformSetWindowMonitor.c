#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  handle; } ;
struct TYPE_19__ {TYPE_1__ x11; TYPE_4__* monitor; int /*<<< orphan*/  resizable; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_20__ {TYPE_3__* window; } ;
typedef  TYPE_4__ _GLFWmonitor ;
struct TYPE_18__ {int /*<<< orphan*/  display; } ;
struct TYPE_16__ {TYPE_2__ x11; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMapRaised (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XMoveResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int) ; 
 TYPE_15__ _glfw ; 
 int /*<<< orphan*/  _glfwInputWindowMonitor (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  _glfwPlatformWindowVisible (TYPE_3__*) ; 
 int /*<<< orphan*/  acquireMonitor (TYPE_3__*) ; 
 int /*<<< orphan*/  releaseMonitor (TYPE_3__*) ; 
 int /*<<< orphan*/  updateNormalHints (TYPE_3__*,int,int) ; 
 int /*<<< orphan*/  updateWindowMode (TYPE_3__*) ; 
 int /*<<< orphan*/  waitForVisibilityNotify (TYPE_3__*) ; 

void _glfwPlatformSetWindowMonitor(_GLFWwindow* window,
                                   _GLFWmonitor* monitor,
                                   int xpos, int ypos,
                                   int width, int height,
                                   int refreshRate)
{
    if (window->monitor == monitor)
    {
        if (monitor)
        {
            if (monitor->window == window)
                acquireMonitor(window);
        }
        else
        {
            if (!window->resizable)
                updateNormalHints(window, width, height);

            XMoveResizeWindow(_glfw.x11.display, window->x11.handle,
                              xpos, ypos, width, height);
        }

        XFlush(_glfw.x11.display);
        return;
    }

    if (window->monitor)
        releaseMonitor(window);

    _glfwInputWindowMonitor(window, monitor);
    updateNormalHints(window, width, height);

    if (window->monitor)
    {
        if (!_glfwPlatformWindowVisible(window))
        {
            XMapRaised(_glfw.x11.display, window->x11.handle);
            waitForVisibilityNotify(window);
        }

        updateWindowMode(window);
        acquireMonitor(window);
    }
    else
    {
        updateWindowMode(window);
        XMoveResizeWindow(_glfw.x11.display, window->x11.handle,
                          xpos, ypos, width, height);
    }

    XFlush(_glfw.x11.display);
}