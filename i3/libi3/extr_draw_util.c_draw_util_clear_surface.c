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
typedef  int /*<<< orphan*/  color_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_SOURCE ; 
 int /*<<< orphan*/  CAIRO_SURFACE_FLUSH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_UNLESS_SURFACE_INITIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_util_set_source_color (TYPE_1__*,int /*<<< orphan*/ ) ; 

void draw_util_clear_surface(surface_t *surface, color_t color) {
    RETURN_UNLESS_SURFACE_INITIALIZED(surface);

    cairo_save(surface->cr);

    /* Using the SOURCE operator will copy both color and alpha information directly
     * onto the surface rather than blending it. This is a bit more efficient and
     * allows better color control for the user when using opacity. */
    cairo_set_operator(surface->cr, CAIRO_OPERATOR_SOURCE);
    draw_util_set_source_color(surface, color);

    cairo_paint(surface->cr);

    /* Make sure we flush the surface for any text drawing operations that could follow.
     * Since we support drawing text via XCB, we need this. */
    CAIRO_SURFACE_FLUSH(surface->surface);

    cairo_restore(surface->cr);
}