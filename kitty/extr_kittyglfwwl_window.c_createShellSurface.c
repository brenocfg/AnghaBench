#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_9__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  shellSurface; scalar_t__ maximized; scalar_t__ title; } ;
struct TYPE_12__ {TYPE_2__ wl; scalar_t__ monitor; } ;
typedef  TYPE_3__ _GLFWwindow ;
struct TYPE_10__ {int /*<<< orphan*/  shell; } ;
struct TYPE_13__ {TYPE_1__ wl; } ;
typedef  int /*<<< orphan*/  GLFWbool ;

/* Variables and functions */
 int /*<<< orphan*/  GLFW_FALSE ; 
 int /*<<< orphan*/  GLFW_PLATFORM_ERROR ; 
 int /*<<< orphan*/  GLFW_TRUE ; 
 TYPE_9__ _glfw ; 
 int /*<<< orphan*/  _glfwInputError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  createDecorations (TYPE_3__*) ; 
 int /*<<< orphan*/  setFullscreen (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setIdleInhibitor (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shellSurfaceListener ; 
 int /*<<< orphan*/  wl_shell_get_shell_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_shell_surface_add_listener (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  wl_shell_surface_set_maximized (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_shell_surface_set_title (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wl_shell_surface_set_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static GLFWbool createShellSurface(_GLFWwindow* window)
{
    if (!_glfw.wl.shell)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: wl_shell protocol not available");
        return GLFW_FALSE;
    }

    window->wl.shellSurface = wl_shell_get_shell_surface(_glfw.wl.shell,
                                                         window->wl.surface);
    if (!window->wl.shellSurface)
    {
        _glfwInputError(GLFW_PLATFORM_ERROR,
                        "Wayland: Shell surface creation failed");
        return GLFW_FALSE;
    }

    wl_shell_surface_add_listener(window->wl.shellSurface,
                                  &shellSurfaceListener,
                                  window);

    if (window->wl.title)
        wl_shell_surface_set_title(window->wl.shellSurface, window->wl.title);

    if (window->monitor)
    {
        setFullscreen(window, window->monitor, 0);
    }
    else if (window->wl.maximized)
    {
        wl_shell_surface_set_maximized(window->wl.shellSurface, NULL);
        setIdleInhibitor(window, GLFW_FALSE);
        createDecorations(window);
    }
    else
    {
        wl_shell_surface_set_toplevel(window->wl.shellSurface);
        setIdleInhibitor(window, GLFW_FALSE);
        createDecorations(window);
    }

    wl_surface_commit(window->wl.surface);

    return GLFW_TRUE;
}