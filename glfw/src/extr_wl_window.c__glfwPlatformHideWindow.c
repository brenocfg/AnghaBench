#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * surface; int /*<<< orphan*/ * toplevel; } ;
struct TYPE_5__ {int /*<<< orphan*/  visible; TYPE_2__ xdg; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  xdg_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xdg_toplevel_destroy (int /*<<< orphan*/ *) ; 

void _glfwPlatformHideWindow(_GLFWwindow* window)
{
    if (window->wl.xdg.toplevel)
    {
        xdg_toplevel_destroy(window->wl.xdg.toplevel);
        xdg_surface_destroy(window->wl.xdg.surface);
        window->wl.xdg.toplevel = NULL;
        window->wl.xdg.surface = NULL;
    }
    window->wl.visible = GLFW_FALSE;
}