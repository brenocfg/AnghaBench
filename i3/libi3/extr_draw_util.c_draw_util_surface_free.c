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
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_3__ {int /*<<< orphan*/ * cr; int /*<<< orphan*/ * surface; int /*<<< orphan*/  gc; } ;
typedef  TYPE_1__ surface_t ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_free_gc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void draw_util_surface_free(xcb_connection_t *conn, surface_t *surface) {
    xcb_free_gc(conn, surface->gc);
    cairo_surface_destroy(surface->surface);
    cairo_destroy(surface->cr);

    /* We need to explicitly set these to NULL to avoid assertion errors in
     * cairo when calling this multiple times. This can happen, for example,
     * when setting the border of a window to none and then closing it. */
    surface->surface = NULL;
    surface->cr = NULL;
}