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
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_endpoint {scalar_t__ ep_mode; } ;
struct usb_device {TYPE_2__* bus; } ;
struct TYPE_4__ {TYPE_1__* methods; } ;
struct TYPE_3__ {scalar_t__ (* set_endpoint_mode ) (struct usb_device*,struct usb_endpoint*,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ USB_EP_MODE_DEFAULT ; 
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ stub1 (struct usb_device*,struct usb_endpoint*,scalar_t__) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 

usb_error_t
usbd_set_endpoint_mode(struct usb_device *udev, struct usb_endpoint *ep,
    uint8_t ep_mode)
{   
	usb_error_t error;
	uint8_t do_unlock;

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	if (udev->bus->methods->set_endpoint_mode != NULL) {
		error = (udev->bus->methods->set_endpoint_mode) (
		    udev, ep, ep_mode);
	} else if (ep_mode != USB_EP_MODE_DEFAULT) {
		error = USB_ERR_INVAL;
	} else {
		error = 0;
	}

	/* only set new mode regardless of error */
	ep->ep_mode = ep_mode;

	if (do_unlock)
		usbd_enum_unlock(udev);
	return (error);
}