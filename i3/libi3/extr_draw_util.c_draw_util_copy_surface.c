#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  cr; int /*<<< orphan*/  surface; } ;
typedef  TYPE_1__ surface_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_SOURCE ; 
 int /*<<< orphan*/  CAIRO_SURFACE_FLUSH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_UNLESS_SURFACE_INITIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ ,double,double,double,double) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ ,int /*<<< orphan*/ ,double,double) ; 

void draw_util_copy_surface(surface_t *src, surface_t *dest, double src_x, double src_y,
                            double dest_x, double dest_y, double width, double height) {
    RETURN_UNLESS_SURFACE_INITIALIZED(src);
    RETURN_UNLESS_SURFACE_INITIALIZED(dest);

    cairo_save(dest->cr);

    /* Using the SOURCE operator will copy both color and alpha information directly
     * onto the surface rather than blending it. This is a bit more efficient and
     * allows better color control for the user when using opacity. */
    cairo_set_operator(dest->cr, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_surface(dest->cr, src->surface, dest_x - src_x, dest_y - src_y);

    cairo_rectangle(dest->cr, dest_x, dest_y, width, height);
    cairo_fill(dest->cr);

    /* Make sure we flush the surface for any text drawing operations that could follow.
     * Since we support drawing text via XCB, we need this. */
    CAIRO_SURFACE_FLUSH(src->surface);
    CAIRO_SURFACE_FLUSH(dest->surface);

    cairo_restore(dest->cr);
}