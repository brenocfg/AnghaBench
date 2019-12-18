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
typedef  int /*<<< orphan*/  uiControl ;
typedef  size_t uiAlign ;
struct gridChild {int /*<<< orphan*/  oldvalign; int /*<<< orphan*/  oldvexpand; int /*<<< orphan*/  oldhalign; int /*<<< orphan*/  oldhexpand; int /*<<< orphan*/ * c; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/ * GTK_WIDGET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtkAligns ; 
 int /*<<< orphan*/  gtk_widget_get_halign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_hexpand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_valign (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_vexpand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_set_halign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_hexpand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  gtk_widget_set_valign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_set_vexpand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uiControlHandle (int /*<<< orphan*/ *) ; 

__attribute__((used)) static GtkWidget *prepare(struct gridChild *gc, uiControl *c, int hexpand, uiAlign halign, int vexpand, uiAlign valign)
{
	GtkWidget *widget;

	gc->c = c;
	widget = GTK_WIDGET(uiControlHandle(gc->c));
	gc->oldhexpand = gtk_widget_get_hexpand(widget);
	gc->oldhalign = gtk_widget_get_halign(widget);
	gc->oldvexpand = gtk_widget_get_vexpand(widget);
	gc->oldvalign = gtk_widget_get_valign(widget);
	gtk_widget_set_hexpand(widget, hexpand != 0);
	gtk_widget_set_halign(widget, gtkAligns[halign]);
	gtk_widget_set_vexpand(widget, vexpand != 0);
	gtk_widget_set_valign(widget, gtkAligns[valign]);
	return widget;
}