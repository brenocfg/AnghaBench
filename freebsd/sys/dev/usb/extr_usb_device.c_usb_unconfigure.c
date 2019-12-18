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
struct TYPE_2__ {scalar_t__ usb_mode; } ;
struct usb_device {int /*<<< orphan*/  curr_config_index; int /*<<< orphan*/  curr_config_no; int /*<<< orphan*/ * cdesc; TYPE_1__ flags; int /*<<< orphan*/ * linux_endpoint_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_CFG_FREE ; 
 int /*<<< orphan*/  USB_IFACE_INDEX_ANY ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  USB_UNCONFIG_INDEX ; 
 int /*<<< orphan*/  USB_UNCONFIG_NO ; 
 int /*<<< orphan*/  usb_cdev_free (struct usb_device*) ; 
 int /*<<< orphan*/  usb_config_parse (struct usb_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_detach_device (struct usb_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_fifo_free_wrap (struct usb_device*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  usb_linux_free_device_p (struct usb_device*) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_free_config_desc (struct usb_device*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_unconfigure(struct usb_device *udev, uint8_t flag)
{
	uint8_t do_unlock;

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	/* detach all interface drivers */
	usb_detach_device(udev, USB_IFACE_INDEX_ANY, flag);

#if USB_HAVE_UGEN
	/* free all FIFOs except control endpoint FIFOs */
	usb_fifo_free_wrap(udev, USB_IFACE_INDEX_ANY, flag);

	/*
	 * Free all cdev's, if any.
	 */
	usb_cdev_free(udev);
#endif

#if USB_HAVE_COMPAT_LINUX
	/* free Linux compat device, if any */
	if (udev->linux_endpoint_start != NULL) {
		usb_linux_free_device_p(udev);
		udev->linux_endpoint_start = NULL;
	}
#endif

	usb_config_parse(udev, USB_IFACE_INDEX_ANY, USB_CFG_FREE);

	/* free "cdesc" after "ifaces" and "endpoints", if any */
	if (udev->cdesc != NULL) {
		if (udev->flags.usb_mode != USB_MODE_DEVICE)
			usbd_free_config_desc(udev, udev->cdesc);
		udev->cdesc = NULL;
	}
	/* set unconfigured state */
	udev->curr_config_no = USB_UNCONFIG_NO;
	udev->curr_config_index = USB_UNCONFIG_INDEX;

	if (do_unlock)
		usbd_enum_unlock(udev);
}