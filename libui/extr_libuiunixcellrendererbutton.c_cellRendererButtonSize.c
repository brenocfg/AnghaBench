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
typedef  int gint ;
typedef  double gfloat ;
typedef  int /*<<< orphan*/  cellRendererButton ;
struct TYPE_6__ {int width; int height; } ;
struct TYPE_5__ {int width; int height; } ;
typedef  TYPE_1__ PangoRectangle ;
typedef  int /*<<< orphan*/  PangoLayout ;
typedef  int /*<<< orphan*/  GtkWidget ;
typedef  TYPE_2__ GdkRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_CELL_RENDERER (int /*<<< orphan*/ *) ; 
 scalar_t__ GTK_TEXT_DIR_RTL ; 
 int /*<<< orphan*/  gtk_cell_renderer_get_alignment (int /*<<< orphan*/ ,double*,double*) ; 
 int /*<<< orphan*/  gtk_cell_renderer_get_padding (int /*<<< orphan*/ ,int*,int*) ; 
 scalar_t__ gtk_widget_get_direction (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_get_pixel_extents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void cellRendererButtonSize(cellRendererButton *c, GtkWidget *widget, PangoLayout *layout, const GdkRectangle *cell_area, gint *xoff, gint *yoff, gint *width, gint *height)
{
	PangoRectangle rect;
	gint xpad, ypad;
	gfloat xalign, yalign;

	gtk_cell_renderer_get_padding(GTK_CELL_RENDERER(c), &xpad, &ypad);
	pango_layout_get_pixel_extents(layout, NULL, &rect);
	if (rect.width > cell_area->width - (2 * xpad))
		rect.width = cell_area->width - (2 * xpad);
	if (rect.height > cell_area->height - (2 * ypad))
		rect.height = cell_area->height - (2 * ypad);

	gtk_cell_renderer_get_alignment(GTK_CELL_RENDERER(c), &xalign, &yalign);
	if (gtk_widget_get_direction(widget) == GTK_TEXT_DIR_RTL)
		xalign = 1.0 - xalign;
	if (xoff != NULL) {
		*xoff = cell_area->width - (rect.width + (2 * xpad));
		*xoff = (gint) ((gfloat) (*xoff) * xalign);
	}
	if (yoff != NULL) {
		*yoff = cell_area->height - (rect.height + (2 * ypad));
		*yoff = (gint) ((gfloat) (*yoff) * yalign);
		if (*yoff < 0)
			*yoff = 0;
	}
	if (width != NULL)
		*width = rect.width - (2 * xpad);
	if (height != NULL)
		*height = rect.height - (2 * ypad);
}