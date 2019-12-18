#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
typedef  int /*<<< orphan*/  xcb_visualtype_t ;
struct TYPE_5__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_1__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_drawable_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_6__ {int width; int height; int /*<<< orphan*/  surface; int /*<<< orphan*/  cr; int /*<<< orphan*/ * visual_type; int /*<<< orphan*/  id; int /*<<< orphan*/  gc; } ;
typedef  TYPE_2__ surface_t ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_xcb_surface_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * visual_type ; 
 int /*<<< orphan*/  xcb_create_gc_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_generate_id (int /*<<< orphan*/ *) ; 
 TYPE_1__* xcb_request_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void draw_util_surface_init(xcb_connection_t *conn, surface_t *surface, xcb_drawable_t drawable,
                            xcb_visualtype_t *visual, int width, int height) {
    surface->id = drawable;
    surface->visual_type = ((visual == NULL) ? visual_type : visual);
    surface->width = width;
    surface->height = height;

    surface->gc = xcb_generate_id(conn);
    xcb_void_cookie_t gc_cookie = xcb_create_gc_checked(conn, surface->gc, surface->id, 0, NULL);

    xcb_generic_error_t *error = xcb_request_check(conn, gc_cookie);
    if (error != NULL) {
        ELOG("Could not create graphical context. Error code: %d. Please report this bug.\n", error->error_code);
    }

    surface->surface = cairo_xcb_surface_create(conn, surface->id, surface->visual_type, width, height);
    surface->cr = cairo_create(surface->surface);
}