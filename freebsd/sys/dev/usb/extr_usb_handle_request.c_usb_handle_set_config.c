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
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  scalar_t__ uint8_t ;
struct usb_xfer {TYPE_1__* xroot; } ;
struct usb_device {int dummy; } ;
struct TYPE_2__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,...) ; 
 int /*<<< orphan*/  USB_ERR_STALLED ; 
 int /*<<< orphan*/  USB_IFACE_INDEX_ANY ; 
 scalar_t__ USB_UNCONFIG_INDEX ; 
 scalar_t__ USB_UNCONFIG_NO ; 
 int /*<<< orphan*/  USB_XFER_LOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_XFER_UNLOCK (struct usb_xfer*) ; 
 scalar_t__ usb_probe_and_attach (struct usb_device*,int /*<<< orphan*/ ) ; 
 scalar_t__ usbd_enum_lock (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_enum_unlock (struct usb_device*) ; 
 scalar_t__ usbd_set_config_index (struct usb_device*,scalar_t__) ; 

__attribute__((used)) static usb_error_t
usb_handle_set_config(struct usb_xfer *xfer, uint8_t conf_no)
{
	struct usb_device *udev = xfer->xroot->udev;
	usb_error_t err = 0;
	uint8_t do_unlock;

	/*
	 * We need to protect against other threads doing probe and
	 * attach:
	 */
	USB_XFER_UNLOCK(xfer);

	/* Prevent re-enumeration */
	do_unlock = usbd_enum_lock(udev);

	if (conf_no == USB_UNCONFIG_NO) {
		conf_no = USB_UNCONFIG_INDEX;
	} else {
		/*
		 * The relationship between config number and config index
		 * is very simple in our case:
		 */
		conf_no--;
	}

	if (usbd_set_config_index(udev, conf_no)) {
		DPRINTF("set config %d failed\n", conf_no);
		err = USB_ERR_STALLED;
		goto done;
	}
	if (usb_probe_and_attach(udev, USB_IFACE_INDEX_ANY)) {
		DPRINTF("probe and attach failed\n");
		err = USB_ERR_STALLED;
		goto done;
	}
done:
	if (do_unlock)
		usbd_enum_unlock(udev);
	USB_XFER_LOCK(xfer);
	return (err);
}