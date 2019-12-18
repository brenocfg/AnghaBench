#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
struct usb_port {int dummy; } ;
struct usb_hub {scalar_t__ nports; struct usb_port* ports; struct uhub_softc* hubsoftc; } ;
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {int speed; TYPE_1__ flags; int /*<<< orphan*/  bus; struct usb_hub* hub; } ;
struct uhub_softc {int dummy; } ;
typedef  enum usb_dev_speed { ____Placeholder_usb_dev_speed } usb_dev_speed ;

/* Variables and functions */
 scalar_t__ USB_MODE_HOST ; 
 struct usb_device* usb_bus_port_get_device (int /*<<< orphan*/ ,struct usb_port*) ; 

uint8_t
uhub_count_active_host_ports(struct usb_device *udev, enum usb_dev_speed speed)
{
	struct uhub_softc *sc;
	struct usb_device *child;
	struct usb_hub *hub;
	struct usb_port *up;
	uint8_t retval = 0;
	uint8_t x;

	if (udev == NULL)
		goto done;
	hub = udev->hub;
	if (hub == NULL)
		goto done;
	sc = hub->hubsoftc;
	if (sc == NULL)
		goto done;

	for (x = 0; x != hub->nports; x++) {
		up = hub->ports + x;
		child = usb_bus_port_get_device(udev->bus, up);
		if (child != NULL &&
		    child->flags.usb_mode == USB_MODE_HOST &&
		    child->speed == speed)
			retval++;
	}
done:
	return (retval);
}