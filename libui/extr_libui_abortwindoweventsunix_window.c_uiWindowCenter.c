#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  widget; } ;
typedef  TYPE_1__ uiWindow ;
typedef  int gint ;
struct TYPE_10__ {int width; int height; } ;
struct TYPE_9__ {int width; int height; } ;
typedef  TYPE_2__ GtkAllocation ;
typedef  int /*<<< orphan*/  GdkWindow ;
typedef  int /*<<< orphan*/  GdkScreen ;
typedef  TYPE_3__ GdkRectangle ;

/* Variables and functions */
 int /*<<< orphan*/  gdk_screen_get_monitor_at_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_screen_get_monitor_workarea (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * gdk_window_get_screen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gtk_widget_get_allocation (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/ * gtk_widget_get_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiWindowSetPosition (TYPE_1__*,int,int) ; 

void uiWindowCenter(uiWindow *w)
{
	gint x, y;
	GtkAllocation winalloc;
	GdkWindow *gdkwin;
	GdkScreen *screen;
	GdkRectangle workarea;

	gtk_widget_get_allocation(w->widget, &winalloc);
	gdkwin = gtk_widget_get_window(w->widget);
	screen = gdk_window_get_screen(gdkwin);
	gdk_screen_get_monitor_workarea(screen,
		gdk_screen_get_monitor_at_window(screen, gdkwin),
		&workarea);

	x = (workarea.width - winalloc.width) / 2;
	y = (workarea.height - winalloc.height) / 2;
	// TODO move up slightly? see what Mutter or GNOME Shell or GNOME Terminal do(es)?
	uiWindowSetPosition(w, x, y);
}