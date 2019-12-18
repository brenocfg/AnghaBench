#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct wl_surface {int dummy; } ;
struct wl_region {int dummy; } ;
struct wl_buffer {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  viewport; int /*<<< orphan*/  subsurface; } ;
typedef  TYPE_2__ _GLFWdecorationWayland ;
struct TYPE_5__ {int /*<<< orphan*/  compositor; int /*<<< orphan*/  viewporter; int /*<<< orphan*/  subcompositor; } ;
struct TYPE_7__ {TYPE_1__ wl; } ;
typedef  scalar_t__ GLFWbool ;

/* Variables and functions */
 TYPE_4__ _glfw ; 
 struct wl_region* wl_compositor_create_region (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_compositor_create_surface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_region_add (struct wl_region*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wl_region_destroy (struct wl_region*) ; 
 int /*<<< orphan*/  wl_subcompositor_get_subsurface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct wl_surface*) ; 
 int /*<<< orphan*/  wl_subsurface_set_position (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wl_surface_attach (int /*<<< orphan*/ ,struct wl_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_set_opaque_region (int /*<<< orphan*/ ,struct wl_region*) ; 
 int /*<<< orphan*/  wp_viewport_set_destination (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wp_viewporter_get_viewport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void createDecoration(_GLFWdecorationWayland* decoration,
                             struct wl_surface* parent,
                             struct wl_buffer* buffer, GLFWbool opaque,
                             int x, int y,
                             int width, int height)
{
    struct wl_region* region;

    decoration->surface = wl_compositor_create_surface(_glfw.wl.compositor);
    decoration->subsurface =
        wl_subcompositor_get_subsurface(_glfw.wl.subcompositor,
                                        decoration->surface, parent);
    wl_subsurface_set_position(decoration->subsurface, x, y);
    decoration->viewport = wp_viewporter_get_viewport(_glfw.wl.viewporter,
                                                      decoration->surface);
    wp_viewport_set_destination(decoration->viewport, width, height);
    wl_surface_attach(decoration->surface, buffer, 0, 0);

    if (opaque)
    {
        region = wl_compositor_create_region(_glfw.wl.compositor);
        wl_region_add(region, 0, 0, width, height);
        wl_surface_set_opaque_region(decoration->surface, region);
        wl_surface_commit(decoration->surface);
        wl_region_destroy(region);
    }
    else
        wl_surface_commit(decoration->surface);
}