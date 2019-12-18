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
struct TYPE_4__ {int /*<<< orphan*/  children; int /*<<< orphan*/  stretchygroup; int /*<<< orphan*/  container; } ;
typedef  TYPE_1__ uiForm ;
struct formChild {int /*<<< orphan*/  oldvalign; int /*<<< orphan*/  oldvexpand; int /*<<< orphan*/  oldhalign; int /*<<< orphan*/  oldhexpand; scalar_t__ stretchy; int /*<<< orphan*/  c; int /*<<< orphan*/  label; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 struct formChild* ctrl (TYPE_1__*,int) ; 
 int /*<<< orphan*/  g_array_remove_index (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gtk_size_group_remove_widget (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_hexpand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_vexpand (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiControlSetParent (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uiUnixControl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiUnixControlSetContainer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void uiFormDelete(uiForm *f, int index)
{
	struct formChild *fc;
	GtkWidget *widget;

	fc = ctrl(f, index);
	widget = GTK_WIDGET(uiControlHandle(fc->c));

	gtk_widget_destroy(fc->label);

	uiControlSetParent(fc->c, NULL);
	uiUnixControlSetContainer(uiUnixControl(fc->c), f->container, TRUE);

	if (fc->stretchy)
		gtk_size_group_remove_widget(f->stretchygroup, widget);
	gtk_widget_set_hexpand(widget, fc->oldhexpand);
	gtk_widget_set_halign(widget, fc->oldhalign);
	gtk_widget_set_vexpand(widget, fc->oldvexpand);
	gtk_widget_set_valign(widget, fc->oldvalign);

	g_array_remove_index(f->children, index);
}