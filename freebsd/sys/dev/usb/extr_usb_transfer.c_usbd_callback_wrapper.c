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
struct TYPE_4__ {struct usb_xfer* curr; } ;
struct usb_xfer_root {TYPE_2__ done_q; int /*<<< orphan*/  cv_drain; int /*<<< orphan*/  bus; int /*<<< orphan*/ * done_m; int /*<<< orphan*/  done_p; int /*<<< orphan*/  xfer_mtx; } ;
struct usb_xfer_queue {scalar_t__ recurse_3; struct usb_xfer* curr; } ;
struct TYPE_3__ {int doing_callback; scalar_t__ draining; scalar_t__ transferring; scalar_t__ started; int /*<<< orphan*/  open; int /*<<< orphan*/  bdma_no_post_sync; scalar_t__ bdma_enable; } ;
struct usb_xfer {scalar_t__ usb_state; TYPE_1__ flags_int; scalar_t__ error; int /*<<< orphan*/  (* callback ) (struct usb_xfer*,scalar_t__) ;struct usb_xfer_root* xroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  MA_NOTOWNED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USBPF_XFERTAP_DONE ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 scalar_t__ USB_IN_POLLING_MODE_FUNC () ; 
 scalar_t__ USB_ST_ERROR ; 
 scalar_t__ USB_ST_SETUP ; 
 scalar_t__ USB_ST_TRANSFERRED ; 
 int /*<<< orphan*/  cv_broadcast (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_owned (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_xfer*,scalar_t__) ; 
 int /*<<< orphan*/  usb_bdma_post_sync (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_command_wrapper (TYPE_2__*,struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ usbd_callback_wrapper_sub (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_power_ref (struct usb_xfer*,int) ; 
 int /*<<< orphan*/  usbpf_xfertap (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbd_callback_wrapper(struct usb_xfer_queue *pq)
{
	struct usb_xfer *xfer = pq->curr;
	struct usb_xfer_root *info = xfer->xroot;

	USB_BUS_LOCK_ASSERT(info->bus, MA_OWNED);
	if ((pq->recurse_3 != 0 || mtx_owned(info->xfer_mtx) == 0) &&
	    USB_IN_POLLING_MODE_FUNC() == 0) {
		/*
	       	 * Cases that end up here:
		 *
		 * 5) HW interrupt done callback or other source.
		 * 6) HW completed transfer during callback
		 */
		DPRINTFN(3, "case 5 and 6\n");

		/*
	         * We have to postpone the callback due to the fact we
	         * will have a Lock Order Reversal, LOR, if we try to
	         * proceed!
		 *
		 * Postponing the callback also ensures that other USB
		 * transfer queues get a chance.
	         */
		(void) usb_proc_msignal(info->done_p,
		    &info->done_m[0], &info->done_m[1]);
		return;
	}
	/*
	 * Cases that end up here:
	 *
	 * 1) We are starting a transfer
	 * 2) We are prematurely calling back a transfer
	 * 3) We are stopping a transfer
	 * 4) We are doing an ordinary callback
	 */
	DPRINTFN(3, "case 1-4\n");
	/* get next USB transfer in the queue */
	info->done_q.curr = NULL;

	/* set flag in case of drain */
	xfer->flags_int.doing_callback = 1;

	USB_BUS_UNLOCK(info->bus);
	USB_BUS_LOCK_ASSERT(info->bus, MA_NOTOWNED);

	/* set correct USB state for callback */
	if (!xfer->flags_int.transferring) {
		xfer->usb_state = USB_ST_SETUP;
		if (!xfer->flags_int.started) {
			/* we got stopped before we even got started */
			USB_BUS_LOCK(info->bus);
			goto done;
		}
	} else {

		if (usbd_callback_wrapper_sub(xfer)) {
			/* the callback has been deferred */
			USB_BUS_LOCK(info->bus);
			goto done;
		}
#if USB_HAVE_POWERD
		/* decrement power reference */
		usbd_transfer_power_ref(xfer, -1);
#endif
		xfer->flags_int.transferring = 0;

		if (xfer->error) {
			xfer->usb_state = USB_ST_ERROR;
		} else {
			/* set transferred state */
			xfer->usb_state = USB_ST_TRANSFERRED;
#if USB_HAVE_BUSDMA
			/* sync DMA memory, if any */
			if (xfer->flags_int.bdma_enable &&
			    (!xfer->flags_int.bdma_no_post_sync)) {
				usb_bdma_post_sync(xfer);
			}
#endif
		}
	}

#if USB_HAVE_PF
	if (xfer->usb_state != USB_ST_SETUP) {
		USB_BUS_LOCK(info->bus);
		usbpf_xfertap(xfer, USBPF_XFERTAP_DONE);
		USB_BUS_UNLOCK(info->bus);
	}
#endif
	/* call processing routine */
	(xfer->callback) (xfer, xfer->error);

	/* pickup the USB mutex again */
	USB_BUS_LOCK(info->bus);

	/*
	 * Check if we got started after that we got cancelled, but
	 * before we managed to do the callback.
	 */
	if ((!xfer->flags_int.open) &&
	    (xfer->flags_int.started) &&
	    (xfer->usb_state == USB_ST_ERROR)) {
		/* clear flag in case of drain */
		xfer->flags_int.doing_callback = 0;
		/* try to loop, but not recursivly */
		usb_command_wrapper(&info->done_q, xfer);
		return;
	}

done:
	/* clear flag in case of drain */
	xfer->flags_int.doing_callback = 0;

	/*
	 * Check if we are draining.
	 */
	if (xfer->flags_int.draining &&
	    (!xfer->flags_int.transferring)) {
		/* "usbd_transfer_drain()" is waiting for end of transfer */
		xfer->flags_int.draining = 0;
		cv_broadcast(&info->cv_drain);
	}

	/* do the next callback, if any */
	usb_command_wrapper(&info->done_q,
	    info->done_q.curr);
}