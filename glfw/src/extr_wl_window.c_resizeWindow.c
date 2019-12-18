#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  viewport; int /*<<< orphan*/  subsurface; } ;
struct TYPE_14__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  viewport; int /*<<< orphan*/  subsurface; } ;
struct TYPE_13__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  viewport; } ;
struct TYPE_12__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  viewport; } ;
struct TYPE_16__ {TYPE_4__ bottom; TYPE_3__ right; TYPE_2__ left; TYPE_1__ top; } ;
struct TYPE_17__ {int scale; int width; int height; TYPE_5__ decorations; int /*<<< orphan*/  transparent; int /*<<< orphan*/  native; } ;
struct TYPE_18__ {TYPE_6__ wl; } ;
typedef  TYPE_7__ _GLFWwindow ;

/* Variables and functions */
 int _GLFW_DECORATION_HORIZONTAL ; 
 int _GLFW_DECORATION_TOP ; 
 int _GLFW_DECORATION_WIDTH ; 
 int /*<<< orphan*/  _glfwInputFramebufferSize (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  _glfwInputWindowContentScale (TYPE_7__*,int,int) ; 
 int /*<<< orphan*/  setOpaqueRegion (TYPE_7__*) ; 
 int /*<<< orphan*/  wl_egl_window_resize (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_subsurface_set_position (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wp_viewport_set_destination (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static void resizeWindow(_GLFWwindow* window)
{
    int scale = window->wl.scale;
    int scaledWidth = window->wl.width * scale;
    int scaledHeight = window->wl.height * scale;
    wl_egl_window_resize(window->wl.native, scaledWidth, scaledHeight, 0, 0);
    if (!window->wl.transparent)
        setOpaqueRegion(window);
    _glfwInputFramebufferSize(window, scaledWidth, scaledHeight);
    _glfwInputWindowContentScale(window, scale, scale);

    if (!window->wl.decorations.top.surface)
        return;

    // Top decoration.
    wp_viewport_set_destination(window->wl.decorations.top.viewport,
                                window->wl.width, _GLFW_DECORATION_TOP);
    wl_surface_commit(window->wl.decorations.top.surface);

    // Left decoration.
    wp_viewport_set_destination(window->wl.decorations.left.viewport,
                                _GLFW_DECORATION_WIDTH, window->wl.height + _GLFW_DECORATION_TOP);
    wl_surface_commit(window->wl.decorations.left.surface);

    // Right decoration.
    wl_subsurface_set_position(window->wl.decorations.right.subsurface,
                               window->wl.width, -_GLFW_DECORATION_TOP);
    wp_viewport_set_destination(window->wl.decorations.right.viewport,
                                _GLFW_DECORATION_WIDTH, window->wl.height + _GLFW_DECORATION_TOP);
    wl_surface_commit(window->wl.decorations.right.surface);

    // Bottom decoration.
    wl_subsurface_set_position(window->wl.decorations.bottom.subsurface,
                               -_GLFW_DECORATION_WIDTH, window->wl.height);
    wp_viewport_set_destination(window->wl.decorations.bottom.viewport,
                                window->wl.width + _GLFW_DECORATION_HORIZONTAL, _GLFW_DECORATION_WIDTH);
    wl_surface_commit(window->wl.decorations.bottom.surface);
}