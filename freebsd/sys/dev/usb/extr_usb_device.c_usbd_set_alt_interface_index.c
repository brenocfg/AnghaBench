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
typedef  scalar_t__ usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_interface {scalar_t__ alt_index; TYPE_1__* idesc; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bAlternateSetting; } ;

/* Variables and functions */
 scalar_t__ USB_ERR_INVAL ; 
 scalar_t__ usb_config_parse (struct usb_device*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  usb_fifo_free_wrap (struct usb_device*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 struct usb_interface* usbd_get_iface (struct usb_device*,scalar_t__) ; 
 scalar_t__ usbd_req_set_alt_interface_no (struct usb_device*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 

usb_error_t
usbd_set_alt_interface_index(struct usb_device *udev,
    uint8_t iface_index, uint8_t alt_index)
{
	struct usb_interface *iface = usbd_get_iface(udev, iface_index);
	usb_error_t err;
	uint8_t do_unlock;

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	if (iface == NULL) {
		err = USB_ERR_INVAL;
		goto done;
	}
	if (iface->alt_index == alt_index) {
		/* 
		 * Optimise away duplicate setting of
		 * alternate setting in USB Host Mode!
		 */
		err = 0;
		goto done;
	}
#if USB_HAVE_UGEN
	/*
	 * Free all generic FIFOs for this interface, except control
	 * endpoint FIFOs:
	 */
	usb_fifo_free_wrap(udev, iface_index, 0);
#endif

	err = usb_config_parse(udev, iface_index, alt_index);
	if (err) {
		goto done;
	}
	if (iface->alt_index != alt_index) {
		/* the alternate setting does not exist */
		err = USB_ERR_INVAL;
		goto done;
	}

	err = usbd_req_set_alt_interface_no(udev, NULL, iface_index,
	    iface->idesc->bAlternateSetting);

done:
	if (do_unlock)
		usbd_enum_unlock(udev);
	return (err);
}