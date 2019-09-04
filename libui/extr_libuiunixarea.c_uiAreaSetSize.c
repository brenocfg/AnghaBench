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
struct TYPE_4__ {int scrollWidth; int scrollHeight; int /*<<< orphan*/  areaWidget; int /*<<< orphan*/  scrolling; } ;
typedef  TYPE_1__ uiArea ;

/* Variables and functions */
 int /*<<< orphan*/  gtk_widget_queue_resize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uiprivUserBug (char*,TYPE_1__*) ; 

void uiAreaSetSize(uiArea *a, int width, int height)
{
	if (!a->scrolling)
		uiprivUserBug("You cannot call uiAreaSetSize() on a non-scrolling uiArea. (area: %p)", a);
	a->scrollWidth = width;
	a->scrollHeight = height;
	gtk_widget_queue_resize(a->areaWidget);
}