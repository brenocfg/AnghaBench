#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  surface; int /*<<< orphan*/  visual_type; int /*<<< orphan*/  gc; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ surface_t ;
typedef  int /*<<< orphan*/  i3String ;
typedef  int /*<<< orphan*/  color_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_SURFACE_FLUSH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RETURN_UNLESS_SURFACE_INITIALIZED (TYPE_1__*) ; 
 int /*<<< orphan*/  cairo_surface_mark_dirty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  draw_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  set_font_colors (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void draw_util_text(i3String *text, surface_t *surface, color_t fg_color, color_t bg_color, int x, int y, int max_width) {
    RETURN_UNLESS_SURFACE_INITIALIZED(surface);

    /* Flush any changes before we draw the text as this might use XCB directly. */
    CAIRO_SURFACE_FLUSH(surface->surface);

    set_font_colors(surface->gc, fg_color, bg_color);
    draw_text(text, surface->id, surface->gc, surface->visual_type, x, y, max_width);

    /* Notify cairo that we (possibly) used another way to draw on the surface. */
    cairo_surface_mark_dirty(surface->surface);
}