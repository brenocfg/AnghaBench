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
struct TYPE_5__ {int /*<<< orphan*/  areaWidget; int /*<<< orphan*/  scrolling; } ;
typedef  TYPE_1__ uiArea ;
struct TYPE_6__ {double width; double height; } ;
typedef  TYPE_2__ GtkAllocation ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_get_allocation (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void loadAreaSize(uiArea *a, double *width, double *height)
{
	GtkAllocation allocation;

	*width = 0;
	*height = 0;
	// don't provide size information for scrolling areas
	if (!a->scrolling) {
		gtk_widget_get_allocation(a->areaWidget, &allocation);
		// these are already in drawing space coordinates
		// for drawing, the size of drawing space has the same value as the widget allocation
		// thanks to tristan in irc.gimp.net/#gtk+
		*width = allocation.width;
		*height = allocation.height;
	}
}