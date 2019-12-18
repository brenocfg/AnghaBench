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
struct TYPE_3__ {int started; scalar_t__ transferring; } ;
struct usb_xfer {TYPE_2__* xroot; TYPE_1__ flags_int; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_callback_ss_done_defer (struct usb_xfer*) ; 

void
usbd_transfer_start(struct usb_xfer *xfer)
{
	if (xfer == NULL) {
		/* transfer is gone */
		return;
	}
	USB_XFER_LOCK_ASSERT(xfer, MA_OWNED);

	/* mark the USB transfer started */

	if (!xfer->flags_int.started) {
		/* lock the BUS lock to avoid races updating flags_int */
		USB_BUS_LOCK(xfer->xroot->bus);
		xfer->flags_int.started = 1;
		USB_BUS_UNLOCK(xfer->xroot->bus);
	}
	/* check if the USB transfer callback is already transferring */

	if (xfer->flags_int.transferring) {
		return;
	}
	USB_BUS_LOCK(xfer->xroot->bus);
	/* call the USB transfer callback */
	usbd_callback_ss_done_defer(xfer);
	USB_BUS_UNLOCK(xfer->xroot->bus);
}