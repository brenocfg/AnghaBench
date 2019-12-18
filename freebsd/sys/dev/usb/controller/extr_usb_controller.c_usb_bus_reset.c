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
struct usb_proc_msg {int dummy; } ;
struct usb_bus_msg {struct usb_bus* bus; } ;
struct usb_bus {scalar_t__ no_explore; int /*<<< orphan*/ * bdev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  usb_bus_resume (struct usb_proc_msg*) ; 
 int /*<<< orphan*/  usb_bus_suspend (struct usb_proc_msg*) ; 

__attribute__((used)) static void
usb_bus_reset(struct usb_proc_msg *pm)
{
	struct usb_bus *bus;

	DPRINTF("\n");

	bus = ((struct usb_bus_msg *)pm)->bus;

	if (bus->bdev == NULL || bus->no_explore != 0)
		return;

	/* a suspend and resume will reset the USB controller */
	usb_bus_suspend(pm);
	usb_bus_resume(pm);
}