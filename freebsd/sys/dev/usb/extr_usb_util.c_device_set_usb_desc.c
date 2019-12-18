#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_interface {TYPE_2__* idesc; } ;
struct TYPE_4__ {scalar_t__ data; } ;
struct usb_device {TYPE_3__* bus; TYPE_1__ scratch; } ;
struct usb_attach_arg {struct usb_interface* iface; struct usb_device* device; } ;
typedef  int /*<<< orphan*/ * device_t ;
struct TYPE_6__ {int /*<<< orphan*/  bdev; } ;
struct TYPE_5__ {scalar_t__ iInterface; } ;

/* Variables and functions */
 scalar_t__ USB_ERR_INVAL ; 
 struct usb_attach_arg* device_get_ivars (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_printf (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_set_desc_copy (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  usb_devinfo (struct usb_device*,char*,int) ; 
 scalar_t__ usbd_ctrl_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_ctrl_unlock (struct usb_device*) ; 
 scalar_t__ usbd_req_get_string_any (struct usb_device*,int /*<<< orphan*/ *,char*,int,scalar_t__) ; 

void
device_set_usb_desc(device_t dev)
{
	struct usb_attach_arg *uaa;
	struct usb_device *udev;
	struct usb_interface *iface;
	char *temp_p;
	usb_error_t err;
	uint8_t do_unlock;

	if (dev == NULL) {
		/* should not happen */
		return;
	}
	uaa = device_get_ivars(dev);
	if (uaa == NULL) {
		/* can happen if called at the wrong time */
		return;
	}
	udev = uaa->device;
	iface = uaa->iface;

	if ((iface == NULL) ||
	    (iface->idesc == NULL) ||
	    (iface->idesc->iInterface == 0)) {
		err = USB_ERR_INVAL;
	} else {
		err = 0;
	}

	/* Protect scratch area */
	do_unlock = usbd_ctrl_lock(udev);

	temp_p = (char *)udev->scratch.data;

	if (err == 0) {
		/* try to get the interface string ! */
		err = usbd_req_get_string_any(udev, NULL, temp_p,
		    sizeof(udev->scratch.data),
		    iface->idesc->iInterface);
	}
	if (err != 0) {
		/* use default description */
		usb_devinfo(udev, temp_p,
		    sizeof(udev->scratch.data));
	}

	if (do_unlock)
		usbd_ctrl_unlock(udev);

	device_set_desc_copy(dev, temp_p);
	device_printf(dev, "<%s> on %s\n", temp_p,
	    device_get_nameunit(udev->bus->bdev));
}