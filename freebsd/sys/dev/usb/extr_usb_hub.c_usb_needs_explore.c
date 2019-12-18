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
typedef  int uint8_t ;
struct usb_bus {int do_probe; int /*<<< orphan*/ * explore_msg; int /*<<< orphan*/  bus_mtx; int /*<<< orphan*/ ** devices; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  USB_BUS_EXPLORE_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 size_t USB_ROOT_HUB_ADDR ; 
 scalar_t__ cold ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ *) ; 
 scalar_t__ usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void
usb_needs_explore(struct usb_bus *bus, uint8_t do_probe)
{
	uint8_t do_unlock;

	DPRINTF("\n");

	if (cold != 0) {
		DPRINTF("Cold\n");
		return;
	}

	if (bus == NULL) {
		DPRINTF("No bus pointer!\n");
		return;
	}
	if ((bus->devices == NULL) ||
	    (bus->devices[USB_ROOT_HUB_ADDR] == NULL)) {
		DPRINTF("No root HUB\n");
		return;
	}
	if (mtx_owned(&bus->bus_mtx)) {
		do_unlock = 0;
	} else {
		USB_BUS_LOCK(bus);
		do_unlock = 1;
	}
	if (do_probe) {
		bus->do_probe = 1;
	}
	if (usb_proc_msignal(USB_BUS_EXPLORE_PROC(bus),
	    &bus->explore_msg[0], &bus->explore_msg[1])) {
		/* ignore */
	}
	if (do_unlock) {
		USB_BUS_UNLOCK(bus);
	}
}