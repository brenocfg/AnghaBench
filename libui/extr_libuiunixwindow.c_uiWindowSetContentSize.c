#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  window; int /*<<< orphan*/  childHolderWidget; } ;
typedef  TYPE_1__ uiWindow ;
typedef  int gint ;
struct TYPE_6__ {scalar_t__ height; scalar_t__ width; } ;
typedef  TYPE_2__ GtkAllocation ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_get_allocation (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  gtk_window_get_size (int /*<<< orphan*/ ,int*,int*) ; 
 int /*<<< orphan*/  gtk_window_resize (int /*<<< orphan*/ ,int,int) ; 

void uiWindowSetContentSize(uiWindow *w, int width, int height)
{
	GtkAllocation childAlloc;
	gint winWidth, winHeight;

	// we need to resize the child holder widget to the given size
	// we can't resize that without running the event loop
	// but we can do gtk_window_set_size()
	// so how do we deal with the differences in sizes?
	// simple arithmetic, of course!

	// from what I can tell, the return from gtk_widget_get_allocation(w->window) and gtk_window_get_size(w->window) will be the same
	// this is not affected by Wayland and not affected by GTK+ builtin CSD
	// so we can safely juse use them to get the real window size!
	// since we're using gtk_window_resize(), use the latter
	gtk_window_get_size(w->window, &winWidth, &winHeight);

	// now get the child holder widget's current allocation
	gtk_widget_get_allocation(w->childHolderWidget, &childAlloc);
	// and punch that out of the window size
	winWidth -= childAlloc.width;
	winHeight -= childAlloc.height;

	// now we just need to add the new size back in
	winWidth += width;
	winHeight += height;
	// and set it
	// this will not move the window in my tests, so we're good
	gtk_window_resize(w->window, winWidth, winHeight);
}