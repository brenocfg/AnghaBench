#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int gint ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_6__ {int /*<<< orphan*/  root; } ;
struct TYPE_4__ {int /*<<< orphan*/  pango_desc; } ;
struct TYPE_5__ {TYPE_1__ specific; } ;
typedef  int /*<<< orphan*/  PangoLayout ;

/* Variables and functions */
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_xcb_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/ * create_layout_with_dpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_cairo_update_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_get_pixel_size (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_set_font_description (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_markup (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  pango_layout_set_text (int /*<<< orphan*/ *,char const*,size_t) ; 
 TYPE_3__* root_screen ; 
 int /*<<< orphan*/  root_visual_type ; 
 TYPE_2__* savedFont ; 

__attribute__((used)) static int predict_text_width_pango(const char *text, size_t text_len, bool pango_markup) {
    /* Create a dummy Pango layout */
    /* root_visual_type is cached in load_pango_font */
    cairo_surface_t *surface = cairo_xcb_surface_create(conn, root_screen->root, root_visual_type, 1, 1);
    cairo_t *cr = cairo_create(surface);
    PangoLayout *layout = create_layout_with_dpi(cr);

    /* Get the font width */
    gint width;
    pango_layout_set_font_description(layout, savedFont->specific.pango_desc);

    if (pango_markup)
        pango_layout_set_markup(layout, text, text_len);
    else
        pango_layout_set_text(layout, text, text_len);

    pango_cairo_update_layout(cr, layout);
    pango_layout_get_pixel_size(layout, &width, NULL);

    /* Free resources */
    g_object_unref(layout);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    return width;
}