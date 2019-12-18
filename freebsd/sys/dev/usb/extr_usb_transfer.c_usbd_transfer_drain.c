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
struct TYPE_4__ {int draining; scalar_t__ doing_callback; } ;
struct usb_xfer {TYPE_1__* xroot; TYPE_2__ flags_int; } ;
struct TYPE_3__ {int /*<<< orphan*/ * xfer_mtx; int /*<<< orphan*/  cv_drain; } ;

/* Variables and functions */
 int /*<<< orphan*/  Giant ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  USB_XFER_LOCK (struct usb_xfer*) ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_XFER_UNLOCK (struct usb_xfer*) ; 
 int WARN_GIANTOK ; 
 int WARN_SLEEPOK ; 
 int /*<<< orphan*/  WITNESS_WARN (int,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cv_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_transfer_pending (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_stop (struct usb_xfer*) ; 

void
usbd_transfer_drain(struct usb_xfer *xfer)
{
	WITNESS_WARN(WARN_GIANTOK | WARN_SLEEPOK, NULL,
	    "usbd_transfer_drain can sleep!");

	if (xfer == NULL) {
		/* transfer is gone */
		return;
	}
	if (xfer->xroot->xfer_mtx != &Giant) {
		USB_XFER_LOCK_ASSERT(xfer, MA_NOTOWNED);
	}
	USB_XFER_LOCK(xfer);

	usbd_transfer_stop(xfer);

	while (usbd_transfer_pending(xfer) || 
	    xfer->flags_int.doing_callback) {

		/* 
		 * It is allowed that the callback can drop its
		 * transfer mutex. In that case checking only
		 * "usbd_transfer_pending()" is not enough to tell if
		 * the USB transfer is fully drained. We also need to
		 * check the internal "doing_callback" flag.
		 */
		xfer->flags_int.draining = 1;

		/*
		 * Wait until the current outstanding USB
		 * transfer is complete !
		 */
		cv_wait(&xfer->xroot->cv_drain, xfer->xroot->xfer_mtx);
	}
	USB_XFER_UNLOCK(xfer);
}