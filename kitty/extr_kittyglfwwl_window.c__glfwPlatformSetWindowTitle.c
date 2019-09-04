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
struct TYPE_6__ {scalar_t__ toplevel; } ;
struct TYPE_5__ {scalar_t__ shellSurface; TYPE_2__ xdg; scalar_t__ title; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
typedef  TYPE_3__ _GLFWwindow ;

/* Variables and functions */
 scalar_t__ _glfw_strdup (char const*) ; 
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  wl_shell_surface_set_title (scalar_t__,char const*) ; 
 int /*<<< orphan*/  xdg_toplevel_set_title (scalar_t__,char const*) ; 

void _glfwPlatformSetWindowTitle(_GLFWwindow* window, const char* title)
{
    if (window->wl.title)
        free(window->wl.title);
    window->wl.title = _glfw_strdup(title);
    if (window->wl.xdg.toplevel)
        xdg_toplevel_set_title(window->wl.xdg.toplevel, title);
    else if (window->wl.shellSurface)
        wl_shell_surface_set_title(window->wl.shellSurface, title);
}