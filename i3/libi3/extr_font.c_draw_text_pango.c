#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_visualtype_t ;
typedef  int /*<<< orphan*/  xcb_drawable_t ;
typedef  int gint ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_3__ {int /*<<< orphan*/  pango_desc; } ;
struct TYPE_4__ {int height; TYPE_1__ specific; } ;
typedef  int /*<<< orphan*/  PangoLayout ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_SOURCE ; 
 int /*<<< orphan*/  PANGO_ELLIPSIZE_END ; 
 int PANGO_SCALE ; 
 int /*<<< orphan*/  PANGO_WRAP_CHAR ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_rgba (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_xcb_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/ * create_layout_with_dpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_cairo_show_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_cairo_update_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_font_alpha ; 
 int /*<<< orphan*/  pango_font_blue ; 
 int /*<<< orphan*/  pango_font_green ; 
 int /*<<< orphan*/  pango_font_red ; 
 int /*<<< orphan*/  pango_layout_get_pixel_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  pango_layout_set_ellipsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_font_description (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_markup (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  pango_layout_set_text (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  pango_layout_set_width (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_layout_set_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* savedFont ; 

__attribute__((used)) static void draw_text_pango(const char *text, size_t text_len,
                            xcb_drawable_t drawable, xcb_visualtype_t *visual, int x, int y,
                            int max_width, bool pango_markup) {
    /* Create the Pango layout */
    /* root_visual_type is cached in load_pango_font */
    cairo_surface_t *surface = cairo_xcb_surface_create(conn, drawable,
                                                        visual, x + max_width, y + savedFont->height);
    cairo_t *cr = cairo_create(surface);
    PangoLayout *layout = create_layout_with_dpi(cr);
    gint height;

    pango_layout_set_font_description(layout, savedFont->specific.pango_desc);
    pango_layout_set_width(layout, max_width * PANGO_SCALE);
    pango_layout_set_wrap(layout, PANGO_WRAP_CHAR);
    pango_layout_set_ellipsize(layout, PANGO_ELLIPSIZE_END);

    if (pango_markup)
        pango_layout_set_markup(layout, text, text_len);
    else
        pango_layout_set_text(layout, text, text_len);

    /* Do the drawing */
    cairo_set_operator(cr, CAIRO_OPERATOR_SOURCE);
    cairo_set_source_rgba(cr, pango_font_red, pango_font_green, pango_font_blue, pango_font_alpha);
    pango_cairo_update_layout(cr, layout);
    pango_layout_get_pixel_size(layout, NULL, &height);
    /* Center the piece of text vertically. */
    int yoffset = (height - savedFont->height) / 2;
    cairo_move_to(cr, x, y - yoffset);
    pango_cairo_show_layout(cr, layout);

    /* Free resources */
    g_object_unref(layout);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);
}