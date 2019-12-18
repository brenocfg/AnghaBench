#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* dragevent; int /*<<< orphan*/  widget; } ;
typedef  TYPE_2__ uiArea ;
struct TYPE_4__ {int /*<<< orphan*/  time; int /*<<< orphan*/  y_root; int /*<<< orphan*/  x_root; int /*<<< orphan*/  button; } ;
typedef  int /*<<< orphan*/  GtkWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GTK_IS_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GTK_WINDOW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_widget_get_toplevel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_is_toplevel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_window_begin_move_drag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivUserBug (char*) ; 

void uiAreaBeginUserWindowMove(uiArea *a)
{
	GtkWidget *toplevel;

	if (a->dragevent == NULL)
		uiprivUserBug("cannot call uiAreaBeginUserWindowMove() outside of a Mouse() with Down != 0");
	// TODO don't we have a libui function for this? did I scrap it?
	// TODO widget or areaWidget?
	toplevel = gtk_widget_get_toplevel(a->widget);
	if (toplevel == NULL) {
		// TODO
		return;
	}
	// the docs say to do this
	if (!gtk_widget_is_toplevel(toplevel)) {
		// TODO
		return;
	}
	if (!GTK_IS_WINDOW(toplevel)) {
		// TODO
		return;
	}
	gtk_window_begin_move_drag(GTK_WINDOW(toplevel),
		a->dragevent->button,
		a->dragevent->x_root,		// TODO are these correct?
		a->dragevent->y_root,
		a->dragevent->time);
}