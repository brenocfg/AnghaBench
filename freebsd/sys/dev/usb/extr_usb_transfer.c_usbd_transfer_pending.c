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
typedef  int uint8_t ;
struct usb_xfer_queue {struct usb_xfer* curr; } ;
struct usb_xfer_root {int /*<<< orphan*/  bus; struct usb_xfer_queue done_q; } ;
struct TYPE_2__ {scalar_t__ transferring; } ;
struct usb_xfer {struct usb_xfer_root* xroot; scalar_t__ wait_queue; TYPE_1__ flags_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 

uint8_t
usbd_transfer_pending(struct usb_xfer *xfer)
{
	struct usb_xfer_root *info;
	struct usb_xfer_queue *pq;

	if (xfer == NULL) {
		/* transfer is gone */
		return (0);
	}
	USB_XFER_LOCK_ASSERT(xfer, MA_OWNED);

	if (xfer->flags_int.transferring) {
		/* trivial case */
		return (1);
	}
	USB_BUS_LOCK(xfer->xroot->bus);
	if (xfer->wait_queue) {
		/* we are waiting on a queue somewhere */
		USB_BUS_UNLOCK(xfer->xroot->bus);
		return (1);
	}
	info = xfer->xroot;
	pq = &info->done_q;

	if (pq->curr == xfer) {
		/* we are currently scheduled for callback */
		USB_BUS_UNLOCK(xfer->xroot->bus);
		return (1);
	}
	/* we are not pending */
	USB_BUS_UNLOCK(xfer->xroot->bus);
	return (0);
}