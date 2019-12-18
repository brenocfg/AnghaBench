#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int can_cancel_immed; } ;
struct usb_xfer {size_t stream_id; TYPE_3__* xroot; scalar_t__ error; TYPE_1__ flags_int; struct usb_endpoint* endpoint; } ;
struct usb_endpoint {int /*<<< orphan*/ * endpoint_q; TYPE_2__* methods; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* enter ) (struct usb_xfer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_command_wrapper (int /*<<< orphan*/ *,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 

void
usbd_pipe_enter(struct usb_xfer *xfer)
{
	struct usb_endpoint *ep;

	USB_XFER_LOCK_ASSERT(xfer, MA_OWNED);

	USB_BUS_LOCK(xfer->xroot->bus);

	ep = xfer->endpoint;

	DPRINTF("enter\n");

	/* the transfer can now be cancelled */
	xfer->flags_int.can_cancel_immed = 1;

	/* enter the transfer */
	(ep->methods->enter) (xfer);

	/* check for transfer error */
	if (xfer->error) {
		/* some error has happened */
		usbd_transfer_done(xfer, 0);
		USB_BUS_UNLOCK(xfer->xroot->bus);
		return;
	}

	/* start the transfer */
	usb_command_wrapper(&ep->endpoint_q[xfer->stream_id], xfer);
	USB_BUS_UNLOCK(xfer->xroot->bus);
}