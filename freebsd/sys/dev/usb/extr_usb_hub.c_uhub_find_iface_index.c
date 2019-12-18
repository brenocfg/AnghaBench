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
struct usb_interface {scalar_t__ subdev; } ;
struct usb_hub {scalar_t__ nports; scalar_t__ ports; TYPE_1__* hubudev; } ;
struct usb_device {int dummy; } ;
struct hub_result {scalar_t__ portno; struct usb_device* udev; scalar_t__ iface_index; } ;
typedef  scalar_t__ device_t ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 scalar_t__ USB_IFACE_MAX ; 
 struct usb_device* usb_bus_port_get_device (int /*<<< orphan*/ ,scalar_t__) ; 
 struct usb_interface* usbd_get_iface (struct usb_device*,scalar_t__) ; 

void
uhub_find_iface_index(struct usb_hub *hub, device_t child,
    struct hub_result *res)
{
	struct usb_interface *iface;
	struct usb_device *udev;
	uint8_t nports;
	uint8_t x;
	uint8_t i;

	nports = hub->nports;
	for (x = 0; x != nports; x++) {
		udev = usb_bus_port_get_device(hub->hubudev->bus,
		    hub->ports + x);
		if (!udev) {
			continue;
		}
		for (i = 0; i != USB_IFACE_MAX; i++) {
			iface = usbd_get_iface(udev, i);
			if (iface &&
			    (iface->subdev == child)) {
				res->iface_index = i;
				res->udev = udev;
				res->portno = x + 1;
				return;
			}
		}
	}
	res->iface_index = 0;
	res->udev = NULL;
	res->portno = 0;
}