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
struct TYPE_3__ {int width; int height; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ surface_t ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_xcb_surface_set_size (int /*<<< orphan*/ ,int,int) ; 

void draw_util_surface_set_size(surface_t *surface, int width, int height) {
    surface->width = width;
    surface->height = height;
    cairo_xcb_surface_set_size(surface->surface, width, height);
}