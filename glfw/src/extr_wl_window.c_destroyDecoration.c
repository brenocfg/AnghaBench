#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * viewport; int /*<<< orphan*/ * subsurface; int /*<<< orphan*/ * surface; } ;
typedef  TYPE_1__ _GLFWdecorationWayland ;

/* Variables and functions */
 int /*<<< orphan*/  wl_subsurface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wp_viewport_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void destroyDecoration(_GLFWdecorationWayland* decoration)
{
    if (decoration->surface)
        wl_surface_destroy(decoration->surface);
    if (decoration->subsurface)
        wl_subsurface_destroy(decoration->subsurface);
    if (decoration->viewport)
        wp_viewport_destroy(decoration->viewport);
    decoration->surface = NULL;
    decoration->subsurface = NULL;
    decoration->viewport = NULL;
}