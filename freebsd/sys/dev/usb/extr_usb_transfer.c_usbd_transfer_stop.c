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
struct TYPE_5__ {int did_close; scalar_t__ can_cancel_immed; scalar_t__ transferring; scalar_t__ started; scalar_t__ open; } ;
struct usb_xfer {size_t stream_id; TYPE_3__* xroot; struct usb_endpoint* endpoint; TYPE_1__ flags_int; int /*<<< orphan*/  error; } ;
struct usb_endpoint {TYPE_4__* endpoint_q; TYPE_2__* methods; } ;
struct TYPE_8__ {struct usb_xfer* curr; } ;
struct TYPE_7__ {int /*<<< orphan*/  bus; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (struct usb_xfer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_xfer*) ; 
 int /*<<< orphan*/  stub2 (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_command_wrapper (TYPE_4__*,int /*<<< orphan*/ *) ; 

void
usbd_transfer_stop(struct usb_xfer *xfer)
{
	struct usb_endpoint *ep;

	if (xfer == NULL) {
		/* transfer is gone */
		return;
	}
	USB_XFER_LOCK_ASSERT(xfer, MA_OWNED);

	/* check if the USB transfer was ever opened */

	if (!xfer->flags_int.open) {
		if (xfer->flags_int.started) {
			/* nothing to do except clearing the "started" flag */
			/* lock the BUS lock to avoid races updating flags_int */
			USB_BUS_LOCK(xfer->xroot->bus);
			xfer->flags_int.started = 0;
			USB_BUS_UNLOCK(xfer->xroot->bus);
		}
		return;
	}
	/* try to stop the current USB transfer */

	USB_BUS_LOCK(xfer->xroot->bus);
	/* override any previous error */
	xfer->error = USB_ERR_CANCELLED;

	/*
	 * Clear "open" and "started" when both private and USB lock
	 * is locked so that we don't get a race updating "flags_int"
	 */
	xfer->flags_int.open = 0;
	xfer->flags_int.started = 0;

	/*
	 * Check if we can cancel the USB transfer immediately.
	 */
	if (xfer->flags_int.transferring) {
		if (xfer->flags_int.can_cancel_immed &&
		    (!xfer->flags_int.did_close)) {
			DPRINTF("close\n");
			/*
			 * The following will lead to an USB_ERR_CANCELLED
			 * error code being passed to the USB callback.
			 */
			(xfer->endpoint->methods->close) (xfer);
			/* only close once */
			xfer->flags_int.did_close = 1;
		} else {
			/* need to wait for the next done callback */
		}
	} else {
		DPRINTF("close\n");

		/* close here and now */
		(xfer->endpoint->methods->close) (xfer);

		/*
		 * Any additional DMA delay is done by
		 * "usbd_transfer_unsetup()".
		 */

		/*
		 * Special case. Check if we need to restart a blocked
		 * endpoint.
		 */
		ep = xfer->endpoint;

		/*
		 * If the current USB transfer is completing we need
		 * to start the next one:
		 */
		if (ep->endpoint_q[xfer->stream_id].curr == xfer) {
			usb_command_wrapper(
			    &ep->endpoint_q[xfer->stream_id], NULL);
		}
	}

	USB_BUS_UNLOCK(xfer->xroot->bus);
}