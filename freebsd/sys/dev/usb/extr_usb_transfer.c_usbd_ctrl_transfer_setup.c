#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_xfer {scalar_t__ address; } ;
struct TYPE_7__ {scalar_t__ bMaxPacketSize; } ;
struct TYPE_6__ {scalar_t__* wMaxPacketSize; } ;
struct TYPE_5__ {scalar_t__ usb_mode; } ;
struct usb_device {scalar_t__ address; int /*<<< orphan*/  device_mtx; TYPE_4__* bus; struct usb_xfer** ctrl_xfer; scalar_t__ clear_stall_errors; TYPE_3__ ddesc; TYPE_2__ ctrl_ep_desc; TYPE_1__ flags; int /*<<< orphan*/ * parent_hub; } ;
struct TYPE_8__ {scalar_t__ control_ep_quirk; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  USB_CTRL_XFER_MAX ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  USB_XFER_LOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_XFER_UNLOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_control_ep_cfg ; 
 int /*<<< orphan*/  usb_control_ep_quirk_cfg ; 
 scalar_t__ usbd_transfer_setup (struct usb_device*,int*,struct usb_xfer**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_start (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_unsetup (struct usb_xfer**,int /*<<< orphan*/ ) ; 

void
usbd_ctrl_transfer_setup(struct usb_device *udev)
{
	struct usb_xfer *xfer;
	uint8_t no_resetup;
	uint8_t iface_index;

	/* check for root HUB */
	if (udev->parent_hub == NULL)
		return;
repeat:

	xfer = udev->ctrl_xfer[0];
	if (xfer) {
		USB_XFER_LOCK(xfer);
		no_resetup =
		    ((xfer->address == udev->address) &&
		    (udev->ctrl_ep_desc.wMaxPacketSize[0] ==
		    udev->ddesc.bMaxPacketSize));
		if (udev->flags.usb_mode == USB_MODE_DEVICE) {
			if (no_resetup) {
				/*
				 * NOTE: checking "xfer->address" and
				 * starting the USB transfer must be
				 * atomic!
				 */
				usbd_transfer_start(xfer);
			}
		}
		USB_XFER_UNLOCK(xfer);
	} else {
		no_resetup = 0;
	}

	if (no_resetup) {
		/*
	         * All parameters are exactly the same like before.
	         * Just return.
	         */
		return;
	}
	/*
	 * Update wMaxPacketSize for the default control endpoint:
	 */
	udev->ctrl_ep_desc.wMaxPacketSize[0] =
	    udev->ddesc.bMaxPacketSize;

	/*
	 * Unsetup any existing USB transfer:
	 */
	usbd_transfer_unsetup(udev->ctrl_xfer, USB_CTRL_XFER_MAX);

	/*
	 * Reset clear stall error counter.
	 */
	udev->clear_stall_errors = 0;

	/*
	 * Try to setup a new USB transfer for the
	 * default control endpoint:
	 */
	iface_index = 0;
	if (usbd_transfer_setup(udev, &iface_index,
	    udev->ctrl_xfer, udev->bus->control_ep_quirk ?
	    usb_control_ep_quirk_cfg : usb_control_ep_cfg, USB_CTRL_XFER_MAX, NULL,
	    &udev->device_mtx)) {
		DPRINTFN(0, "could not setup default "
		    "USB transfer\n");
	} else {
		goto repeat;
	}
}