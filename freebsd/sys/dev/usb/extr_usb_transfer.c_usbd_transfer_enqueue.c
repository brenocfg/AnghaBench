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
struct usb_xfer_queue {int /*<<< orphan*/  head; } ;
struct usb_xfer {struct usb_xfer_queue* wait_queue; } ;

/* Variables and functions */
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_entry ; 

void
usbd_transfer_enqueue(struct usb_xfer_queue *pq, struct usb_xfer *xfer)
{
	/*
	 * Insert the USB transfer into the queue, if it is not
	 * already on a USB transfer queue:
	 */
	if (xfer->wait_queue == NULL) {
		xfer->wait_queue = pq;
		TAILQ_INSERT_TAIL(&pq->head, xfer, wait_entry);
	}
}