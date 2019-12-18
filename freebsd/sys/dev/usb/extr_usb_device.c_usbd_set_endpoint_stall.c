#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  size_t usb_stream_t ;
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct usb_xfer {int dummy; } ;
struct usb_endpoint {int is_stalled; TYPE_3__* endpoint_q; scalar_t__ toggle_next; TYPE_1__* edesc; } ;
struct usb_device {TYPE_4__* bus; } ;
struct TYPE_9__ {TYPE_2__* methods; } ;
struct TYPE_8__ {struct usb_xfer* curr; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* clear_stall ) (struct usb_device*,struct usb_endpoint*) ;int /*<<< orphan*/  (* set_stall ) (struct usb_device*,struct usb_endpoint*,int*) ;int /*<<< orphan*/  (* xfer_stall ) (struct usb_xfer*) ;} ;
struct TYPE_6__ {int bmAttributes; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int UE_BULK ; 
 int UE_INTERRUPT ; 
 int UE_XFERTYPE ; 
 int /*<<< orphan*/  USB_BUS_LOCK (TYPE_4__*) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (TYPE_4__*) ; 
 size_t USB_MAX_EP_STREAMS ; 
 int /*<<< orphan*/  stub1 (struct usb_xfer*) ; 
 int /*<<< orphan*/  stub2 (struct usb_device*,struct usb_endpoint*,int*) ; 
 int /*<<< orphan*/  stub3 (struct usb_device*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  usb_command_wrapper (TYPE_3__*,struct usb_xfer*) ; 

usb_error_t
usbd_set_endpoint_stall(struct usb_device *udev, struct usb_endpoint *ep,
    uint8_t do_stall)
{
	struct usb_xfer *xfer;
	usb_stream_t x;
	uint8_t et;
	uint8_t was_stalled;

	if (ep == NULL) {
		/* nothing to do */
		DPRINTF("Cannot find endpoint\n");
		/*
		 * Pretend that the clear or set stall request is
		 * successful else some USB host stacks can do
		 * strange things, especially when a control endpoint
		 * stalls.
		 */
		return (0);
	}
	et = (ep->edesc->bmAttributes & UE_XFERTYPE);

	if ((et != UE_BULK) &&
	    (et != UE_INTERRUPT)) {
		/*
	         * Should not stall control
	         * nor isochronous endpoints.
	         */
		DPRINTF("Invalid endpoint\n");
		return (0);
	}
	USB_BUS_LOCK(udev->bus);

	/* store current stall state */
	was_stalled = ep->is_stalled;

	/* check for no change */
	if (was_stalled && do_stall) {
		/* if the endpoint is already stalled do nothing */
		USB_BUS_UNLOCK(udev->bus);
		DPRINTF("No change\n");
		return (0);
	}
	/* set stalled state */
	ep->is_stalled = 1;

	if (do_stall || (!was_stalled)) {
		if (!was_stalled) {
			for (x = 0; x != USB_MAX_EP_STREAMS; x++) {
				/* lookup the current USB transfer, if any */
				xfer = ep->endpoint_q[x].curr;
				if (xfer != NULL) {
					/*
					 * The "xfer_stall" method
					 * will complete the USB
					 * transfer like in case of a
					 * timeout setting the error
					 * code "USB_ERR_STALLED".
					 */
					(udev->bus->methods->xfer_stall) (xfer);
				}
			}
		}
		(udev->bus->methods->set_stall) (udev, ep, &do_stall);
	}
	if (!do_stall) {
		ep->toggle_next = 0;	/* reset data toggle */
		ep->is_stalled = 0;	/* clear stalled state */

		(udev->bus->methods->clear_stall) (udev, ep);

		/* start the current or next transfer, if any */
		for (x = 0; x != USB_MAX_EP_STREAMS; x++) {
			usb_command_wrapper(&ep->endpoint_q[x],
			    ep->endpoint_q[x].curr);
		}
	}
	USB_BUS_UNLOCK(udev->bus);
	return (0);
}