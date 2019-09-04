#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ toplevel; } ;
struct TYPE_7__ {scalar_t__ maximized; scalar_t__ shellSurface; TYPE_1__ xdg; } ;
struct TYPE_8__ {TYPE_2__ wl; scalar_t__ monitor; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ GLFW_FALSE ; 
 int /*<<< orphan*/  _glfwInputWindowMonitor (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_shell_surface_set_toplevel (scalar_t__) ; 
 int /*<<< orphan*/  xdg_toplevel_unset_fullscreen (scalar_t__) ; 
 int /*<<< orphan*/  xdg_toplevel_unset_maximized (scalar_t__) ; 

void _glfwPlatformRestoreWindow(_GLFWwindow* window)
{
    if (window->wl.xdg.toplevel)
    {
        if (window->monitor)
            xdg_toplevel_unset_fullscreen(window->wl.xdg.toplevel);
        if (window->wl.maximized)
            xdg_toplevel_unset_maximized(window->wl.xdg.toplevel);
        // There is no way to unset minimized, or even to know if we are
        // minimized, so there is nothing to do here.
    }
    else if (window->wl.shellSurface)
    {
        if (window->monitor || window->wl.maximized)
            wl_shell_surface_set_toplevel(window->wl.shellSurface);
    }
    _glfwInputWindowMonitor(window, NULL);
    window->wl.maximized = GLFW_FALSE;
}