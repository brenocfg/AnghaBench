#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  endGrab (TYPE_1__*) ; 
 int /*<<< orphan*/  gtk_widget_hide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setActive (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void hidePopup(uiprivDateTimePickerWidget *d)
{
	endGrab(d);
	gtk_widget_hide(d->window);
	setActive(d, FALSE);
}