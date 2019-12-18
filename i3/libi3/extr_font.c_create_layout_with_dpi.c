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
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  PangoLayout ;
typedef  int /*<<< orphan*/  PangoContext ;

/* Variables and functions */
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_dpi_value () ; 
 int /*<<< orphan*/  pango_cairo_context_set_resolution (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * pango_cairo_create_context (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * pango_layout_new (int /*<<< orphan*/ *) ; 

__attribute__((used)) static PangoLayout *create_layout_with_dpi(cairo_t *cr) {
    PangoLayout *layout;
    PangoContext *context;

    context = pango_cairo_create_context(cr);
    pango_cairo_context_set_resolution(context, get_dpi_value());
    layout = pango_layout_new(context);
    g_object_unref(context);

    return layout;
}