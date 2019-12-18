#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  pango_desc; } ;
struct TYPE_7__ {int /*<<< orphan*/  type; int /*<<< orphan*/  height; TYPE_1__ specific; } ;
typedef  TYPE_2__ i3Font ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_8__ {int /*<<< orphan*/  root; } ;
typedef  int /*<<< orphan*/  PangoLayout ;

/* Variables and functions */
 int /*<<< orphan*/  ELOG (char*,char const*) ; 
 int /*<<< orphan*/  FONT_TYPE_PANGO ; 
 int /*<<< orphan*/  LOG (char*,int /*<<< orphan*/ ,int) ; 
 int PANGO_SCALE ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_xcb_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  conn ; 
 int /*<<< orphan*/ * create_layout_with_dpi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_visualtype (TYPE_3__*) ; 
 int /*<<< orphan*/  pango_font_description_from_string (char const*) ; 
 int /*<<< orphan*/  pango_font_description_get_family (int /*<<< orphan*/ ) ; 
 int pango_font_description_get_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_get_pixel_size (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_set_font_description (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* root_screen ; 
 int /*<<< orphan*/  root_visual_type ; 

__attribute__((used)) static bool load_pango_font(i3Font *font, const char *desc) {
    /* Load the font description */
    font->specific.pango_desc = pango_font_description_from_string(desc);
    if (!font->specific.pango_desc) {
        ELOG("Could not open font %s with Pango, fallback to X font.\n", desc);
        return false;
    }

    LOG("Using Pango font %s, size %d\n",
        pango_font_description_get_family(font->specific.pango_desc),
        pango_font_description_get_size(font->specific.pango_desc) / PANGO_SCALE);

    /* We cache root_visual_type here, since you must call
     * load_pango_font before any other pango function
     * that would need root_visual_type */
    root_visual_type = get_visualtype(root_screen);

    /* Create a dummy Pango layout to compute the font height */
    cairo_surface_t *surface = cairo_xcb_surface_create(conn, root_screen->root, root_visual_type, 1, 1);
    cairo_t *cr = cairo_create(surface);
    PangoLayout *layout = create_layout_with_dpi(cr);
    pango_layout_set_font_description(layout, font->specific.pango_desc);

    /* Get the font height */
    gint height;
    pango_layout_get_pixel_size(layout, NULL, &height);
    font->height = height;

    /* Free resources */
    g_object_unref(layout);
    cairo_destroy(cr);
    cairo_surface_destroy(surface);

    /* Set the font type and return successfully */
    font->type = FONT_TYPE_PANGO;
    return true;
}