#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct usb_bus {TYPE_3__* reset_msg; int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int /*<<< orphan*/ * tqe_prev; } ;
struct TYPE_5__ {TYPE_2__ pm_qentry; } ;
struct TYPE_7__ {TYPE_1__ hdr; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_EXPLORE_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (struct usb_bus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,TYPE_3__*,TYPE_3__*) ; 

void
usb_bus_reset_async_locked(struct usb_bus *bus)
{
	USB_BUS_LOCK_ASSERT(bus, MA_OWNED);

	DPRINTF("\n");

	if (bus->reset_msg[0].hdr.pm_qentry.tqe_prev != NULL ||
	    bus->reset_msg[1].hdr.pm_qentry.tqe_prev != NULL) {
		DPRINTF("Reset already pending\n");
		return;
	}

	device_printf(bus->parent, "Resetting controller\n");

	usb_proc_msignal(USB_BUS_EXPLORE_PROC(bus),
	    &bus->reset_msg[0], &bus->reset_msg[1]);
}