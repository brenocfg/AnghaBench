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
struct usb_bus {int /*<<< orphan*/  bdev; int /*<<< orphan*/ * shutdown_msg; } ;
typedef  int /*<<< orphan*/  device_t ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  USB_BUS_EXPLORE_PROC (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 struct usb_bus* device_get_softc (int /*<<< orphan*/ ) ; 
 scalar_t__ usb_no_shutdown_wait ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usb_proc_mwait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
usb_shutdown(device_t dev)
{
	struct usb_bus *bus = device_get_softc(dev);

	DPRINTF("\n");

	if (bus == NULL) {
		/* was never setup properly */
		return (0);
	}

	DPRINTF("%s: Controller shutdown\n", device_get_nameunit(bus->bdev));

	USB_BUS_LOCK(bus);
	usb_proc_msignal(USB_BUS_EXPLORE_PROC(bus),
	    &bus->shutdown_msg[0], &bus->shutdown_msg[1]);
	if (usb_no_shutdown_wait == 0) {
		/* wait for shutdown callback to be executed */
		usb_proc_mwait(USB_BUS_EXPLORE_PROC(bus),
		    &bus->shutdown_msg[0], &bus->shutdown_msg[1]);
	}
	USB_BUS_UNLOCK(bus);

	DPRINTF("%s: Controller shutdown complete\n",
	    device_get_nameunit(bus->bdev));

	return (0);
}