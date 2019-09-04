#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  PangoFontDescription ;
typedef  int /*<<< orphan*/  PangoFont ;
typedef  int /*<<< orphan*/  PangoContext ;

/* Variables and functions */
 int /*<<< orphan*/  g_error (char*) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mkGenericPangoCairoContext () ; 
 int /*<<< orphan*/  pango_cairo_font_map_get_default () ; 
 int /*<<< orphan*/ * pango_font_map_load_font (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

PangoFont *pangoDescToPangoFont(PangoFontDescription *pdesc)
{
	PangoFont *f;
	PangoContext *context;

	// in this case, the context is necessary for the metrics to be correct
	context = mkGenericPangoCairoContext();
	f = pango_font_map_load_font(pango_cairo_font_map_get_default(), context, pdesc);
	if (f == NULL) {
		// LONGTERM
		g_error("[libui] no match in pangoDescToPangoFont(); report to andlabs");
	}
	g_object_unref(context);
	return f;
}