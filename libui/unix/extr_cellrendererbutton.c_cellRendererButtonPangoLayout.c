#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  text; } ;
typedef  TYPE_1__ cellRendererButton ;
typedef  int /*<<< orphan*/  PangoLayout ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  PANGO_ALIGN_CENTER ; 
 int /*<<< orphan*/  PANGO_ELLIPSIZE_NONE ; 
 int /*<<< orphan*/  PANGO_WRAP_CHAR ; 
 int /*<<< orphan*/ * gtk_widget_create_pango_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_alignment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_ellipsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_width (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_layout_set_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static PangoLayout *cellRendererButtonPangoLayout(cellRendererButton *c, GtkWidget *widget)
{
	PangoLayout *layout;

	layout = gtk_widget_create_pango_layout(widget, c->text);
	pango_layout_set_ellipsize(layout, PANGO_ELLIPSIZE_NONE);
	pango_layout_set_width(layout, -1);
	pango_layout_set_wrap(layout, PANGO_WRAP_CHAR);
	pango_layout_set_alignment(layout, PANGO_ALIGN_CENTER);
	return layout;
}