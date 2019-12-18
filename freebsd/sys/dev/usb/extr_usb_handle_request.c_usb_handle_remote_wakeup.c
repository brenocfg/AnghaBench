#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_xfer {TYPE_1__* xroot; } ;
struct TYPE_4__ {int remote_wakeup; } ;
struct usb_device {struct usb_bus* bus; TYPE_2__ flags; } ;
struct usb_bus {int dummy; } ;
struct TYPE_3__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_BUS_LOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (struct usb_bus*) ; 
 int /*<<< orphan*/  usb_bus_power_update (struct usb_bus*) ; 

__attribute__((used)) static usb_error_t
usb_handle_remote_wakeup(struct usb_xfer *xfer, uint8_t is_on)
{
	struct usb_device *udev;
	struct usb_bus *bus;

	udev = xfer->xroot->udev;
	bus = udev->bus;

	USB_BUS_LOCK(bus);

	if (is_on) {
		udev->flags.remote_wakeup = 1;
	} else {
		udev->flags.remote_wakeup = 0;
	}

	USB_BUS_UNLOCK(bus);

#if USB_HAVE_POWERD
	/* In case we are out of sync, update the power state. */
	usb_bus_power_update(udev->bus);
#endif
	return (0);			/* success */
}