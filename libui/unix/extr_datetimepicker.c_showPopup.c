#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/ * window; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  int /*<<< orphan*/  gint ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 scalar_t__ GTK_IS_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  allocationToScreen (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_widget_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_show (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_get_group (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_group_add_window (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_window_move (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hidePopup (TYPE_1__*) ; 
 int /*<<< orphan*/  setActive (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  startGrab (TYPE_1__*) ; 

__attribute__((used)) static void showPopup(uiprivDateTimePickerWidget *d)
{
	GtkWidget *toplevel;
	gint x, y;

	// GtkComboBox does it
	toplevel = gtk_widget_get_toplevel(GTK_WIDGET(d));
	if (GTK_IS_WINDOW(toplevel))
		gtk_window_group_add_window(gtk_window_get_group(GTK_WINDOW(toplevel)), GTK_WINDOW(d->window));

	allocationToScreen(d, &x, &y);
	gtk_window_move(GTK_WINDOW(d->window), x, y);

	gtk_widget_show(d->window);
	setActive(d, TRUE);

	if (!startGrab(d))
		hidePopup(d);
}