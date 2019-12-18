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
struct TYPE_4__ {int /*<<< orphan*/  controls; int /*<<< orphan*/  stretchygroup; int /*<<< orphan*/  container; } ;
typedef  TYPE_1__ uiBox ;
struct boxChild {int /*<<< orphan*/  oldvalign; int /*<<< orphan*/  oldvexpand; int /*<<< orphan*/  oldhalign; int /*<<< orphan*/  oldhexpand; scalar_t__ stretchy; int /*<<< orphan*/  c; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 struct boxChild* ctrl (TYPE_1__*,int) ; 
 int /*<<< orphan*/  g_array_remove_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_size_group_remove_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_hexpand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_vexpand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlSetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiUnixControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiUnixControlSetContainer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uiBoxDelete(uiBox *b, int index)
{
	struct boxChild *bc;
	GtkWidget *widget;

	bc = ctrl(b, index);
	widget = GTK_WIDGET(uiControlHandle(bc->c));

	uiControlSetParent(bc->c, NULL);
	uiUnixControlSetContainer(uiUnixControl(bc->c), b->container, TRUE);

	if (bc->stretchy)
		gtk_size_group_remove_widget(b->stretchygroup, widget);
	gtk_widget_set_hexpand(widget, bc->oldhexpand);
	gtk_widget_set_halign(widget, bc->oldhalign);
	gtk_widget_set_vexpand(widget, bc->oldvexpand);
	gtk_widget_set_valign(widget, bc->oldvalign);

	g_array_remove_index(b->controls, index);
}