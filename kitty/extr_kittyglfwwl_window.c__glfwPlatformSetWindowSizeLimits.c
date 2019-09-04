#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ toplevel; } ;
struct TYPE_9__ {int /*<<< orphan*/  surface; TYPE_2__ xdg; } ;
struct TYPE_10__ {TYPE_3__ wl; } ;
typedef  TYPE_4__ _GLFWwindow ;
struct TYPE_7__ {scalar_t__ wmBase; } ;
struct TYPE_11__ {TYPE_1__ wl; } ;

/* Variables and functions */
 int GLFW_DONT_CARE ; 
 TYPE_6__ _glfw ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xdg_toplevel_set_max_size (scalar_t__,int,int) ; 
 int /*<<< orphan*/  xdg_toplevel_set_min_size (scalar_t__,int,int) ; 

void _glfwPlatformSetWindowSizeLimits(_GLFWwindow* window,
                                      int minwidth, int minheight,
                                      int maxwidth, int maxheight)
{
    if (_glfw.wl.wmBase)
    {
        if (window->wl.xdg.toplevel)
        {
            if (minwidth == GLFW_DONT_CARE || minheight == GLFW_DONT_CARE)
                minwidth = minheight = 0;
            if (maxwidth == GLFW_DONT_CARE || maxheight == GLFW_DONT_CARE)
                maxwidth = maxheight = 0;
            xdg_toplevel_set_min_size(window->wl.xdg.toplevel, minwidth, minheight);
            xdg_toplevel_set_max_size(window->wl.xdg.toplevel, maxwidth, maxheight);
            wl_surface_commit(window->wl.surface);
        }
    }
    else
    {
        // TODO: find out how to trigger a resize.
        // The actual limits are checked in the wl_shell_surface::configure handler.
    }
}