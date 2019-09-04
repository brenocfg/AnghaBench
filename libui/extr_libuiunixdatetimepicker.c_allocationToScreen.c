#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;
typedef  scalar_t__ gint ;
struct TYPE_13__ {scalar_t__ x; scalar_t__ width; scalar_t__ y; scalar_t__ height; } ;
struct TYPE_12__ {scalar_t__ x; scalar_t__ y; scalar_t__ width; scalar_t__ height; } ;
struct TYPE_11__ {scalar_t__ width; int height; } ;
typedef  TYPE_2__ GtkRequisition ;
typedef  TYPE_3__ GtkAllocation ;
typedef  int /*<<< orphan*/  GdkWindow ;
typedef  int /*<<< orphan*/  GdkScreen ;
typedef  TYPE_4__ GdkRectangle ;

/* Variables and functions */
 scalar_t__ GTK_TEXT_DIR_RTL ; 
 int /*<<< orphan*/  GTK_WIDGET (TYPE_1__*) ; 
 int /*<<< orphan*/  gdk_screen_get_monitor_at_window (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdk_screen_get_monitor_workarea (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  gdk_window_get_root_coords (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  gtk_widget_get_allocation (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ gtk_widget_get_direction (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_has_window (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_widget_get_preferred_size (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * gtk_widget_get_screen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * gtk_widget_get_window (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void allocationToScreen(uiprivDateTimePickerWidget *d, gint *x, gint *y)
{
	GdkWindow *window;
	GtkAllocation a;
	GtkRequisition aWin;
	GdkScreen *screen;
	GdkRectangle workarea;
	int otherY;

	gtk_widget_get_allocation(GTK_WIDGET(d), &a);
	gtk_widget_get_preferred_size(d->window, &aWin, NULL);
	*x = 0;
	*y = 0;
	if (!gtk_widget_get_has_window(GTK_WIDGET(d))) {
		*x = a.x;
		*y = a.y;
	}
	window = gtk_widget_get_window(GTK_WIDGET(d));
	gdk_window_get_root_coords(window, *x, *y, x, y);
	if (gtk_widget_get_direction(GTK_WIDGET(d)) == GTK_TEXT_DIR_RTL)
		*x += a.width - aWin.width;

	// now adjust to prevent the box from going offscreen
	screen = gtk_widget_get_screen(GTK_WIDGET(d));
	gdk_screen_get_monitor_workarea(screen,
		gdk_screen_get_monitor_at_window(screen, window),
		&workarea);
	if (*x < workarea.x)					// too far to the left?
		*x = workarea.x;
	else if (*x + aWin.width > (workarea.x + workarea.width))	// too far to the right?
		*x = (workarea.x + workarea.width) - aWin.width;
	// this isn't the same algorithm used by GtkComboBox
	// first, get our two choices; *y for down and otherY for up
	otherY = *y - aWin.height;
	*y += a.height;
	// and use otherY if we're too low
	if (*y + aWin.height >= workarea.y + workarea.height)
		*y = otherY;
}