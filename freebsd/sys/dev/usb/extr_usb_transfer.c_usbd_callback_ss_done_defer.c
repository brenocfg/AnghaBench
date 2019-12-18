#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct usb_xfer_queue {scalar_t__ recurse_2; int /*<<< orphan*/  recurse_1; struct usb_xfer* curr; } ;
struct usb_xfer_root {int /*<<< orphan*/ * done_m; int /*<<< orphan*/  done_p; int /*<<< orphan*/  bus; struct usb_xfer_queue done_q; } ;
struct usb_xfer {struct usb_xfer_root* xroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_enqueue (struct usb_xfer_queue*,struct usb_xfer*) ; 

__attribute__((used)) static void
usbd_callback_ss_done_defer(struct usb_xfer *xfer)
{
	struct usb_xfer_root *info = xfer->xroot;
	struct usb_xfer_queue *pq = &info->done_q;

	USB_BUS_LOCK_ASSERT(xfer->xroot->bus, MA_OWNED);

	if (pq->curr != xfer) {
		usbd_transfer_enqueue(pq, xfer);
	}
	if (!pq->recurse_1) {

		/*
	         * We have to postpone the callback due to the fact we
	         * will have a Lock Order Reversal, LOR, if we try to
	         * proceed !
	         */
		(void) usb_proc_msignal(info->done_p,
		    &info->done_m[0], &info->done_m[1]);
	} else {
		/* clear second recurse flag */
		pq->recurse_2 = 0;
	}
	return;

}