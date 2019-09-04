#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * mouse; int /*<<< orphan*/ * keyboard; int /*<<< orphan*/  window; } ;
typedef  TYPE_1__ uiprivDateTimePickerWidget ;

/* Variables and functions */
 int /*<<< orphan*/  GDK_CURRENT_TIME ; 
 int /*<<< orphan*/  gdk_device_ungrab (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gtk_device_grab_remove (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void endGrab(uiprivDateTimePickerWidget *d)
{
	if (d->keyboard != NULL)
		gdk_device_ungrab(d->keyboard, GDK_CURRENT_TIME);
	gdk_device_ungrab(d->mouse, GDK_CURRENT_TIME);
	gtk_device_grab_remove(d->window, d->mouse);
	d->keyboard = NULL;
	d->mouse = NULL;
}