#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  handle; } ;
struct TYPE_12__ {TYPE_2__ x11; int /*<<< orphan*/  resizable; TYPE_1__* monitor; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_11__ {int /*<<< orphan*/  display; } ;
struct TYPE_13__ {TYPE_3__ x11; } ;
struct TYPE_9__ {TYPE_4__* window; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFlush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XResizeWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 TYPE_8__ _glfw ; 
 int /*<<< orphan*/  acquireMonitor (TYPE_4__*) ; 
 int /*<<< orphan*/  updateNormalHints (TYPE_4__*,int,int) ; 

void _glfwPlatformSetWindowSize(_GLFWwindow* window, int width, int height)
{
    if (window->monitor)
    {
        if (window->monitor->window == window)
            acquireMonitor(window);
    }
    else
    {
        if (!window->resizable)
            updateNormalHints(window, width, height);

        XResizeWindow(_glfw.x11.display, window->x11.handle, width, height);
    }

    XFlush(_glfw.x11.display);
}