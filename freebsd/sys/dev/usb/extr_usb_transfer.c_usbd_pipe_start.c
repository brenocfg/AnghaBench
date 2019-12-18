#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct usb_xfer_root {int /*<<< orphan*/  bus; struct usb_device* udev; } ;
struct usb_xfer_queue {struct usb_xfer* curr; } ;
struct TYPE_15__ {int can_cancel_immed; } ;
struct TYPE_9__ {scalar_t__ stall_pipe; } ;
struct usb_xfer {scalar_t__ nframes; scalar_t__ interval; scalar_t__ error; TYPE_7__ flags_int; scalar_t__ aframes; struct usb_xfer_root* xroot; TYPE_1__ flags; struct usb_endpoint* endpoint; } ;
struct usb_endpoint {int is_stalled; TYPE_8__* methods; TYPE_6__* edesc; } ;
struct TYPE_11__ {scalar_t__ usb_mode; } ;
struct usb_device {TYPE_5__* bus; TYPE_3__ flags; int /*<<< orphan*/ * cs_msg; TYPE_2__** ctrl_xfer; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* start ) (struct usb_xfer*) ;} ;
struct TYPE_14__ {int bmAttributes; } ;
struct TYPE_13__ {TYPE_4__* methods; } ;
struct TYPE_12__ {int /*<<< orphan*/  (* clear_stall ) (struct usb_device*,struct usb_endpoint*) ;int /*<<< orphan*/  (* set_stall ) (struct usb_device*,struct usb_endpoint*,int*) ;} ;
struct TYPE_10__ {struct usb_xfer_root* xroot; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  DPRINTFN (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int UE_BULK ; 
 int UE_CONTROL ; 
 int UE_INTERRUPT ; 
 int UE_ISOCHRONOUS ; 
 int UE_XFERTYPE ; 
 int /*<<< orphan*/  USBPF_XFERTAP_SUBMIT ; 
 int /*<<< orphan*/  USB_BUS_CS_PROC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_MODE_DEVICE ; 
 int /*<<< orphan*/  stub1 (struct usb_device*,struct usb_endpoint*,int*) ; 
 int /*<<< orphan*/  stub2 (struct usb_device*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  stub3 (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_proc_msignal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_start_cb ; 
 int /*<<< orphan*/  usbd_transfer_timeout_ms (struct usb_xfer*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  usbpf_xfertap (struct usb_xfer*,int /*<<< orphan*/ ) ; 

void
usbd_pipe_start(struct usb_xfer_queue *pq)
{
	struct usb_endpoint *ep;
	struct usb_xfer *xfer;
	uint8_t type;

	xfer = pq->curr;
	ep = xfer->endpoint;

	USB_BUS_LOCK_ASSERT(xfer->xroot->bus, MA_OWNED);

	/*
	 * If the endpoint is already stalled we do nothing !
	 */
	if (ep->is_stalled) {
		return;
	}
	/*
	 * Check if we are supposed to stall the endpoint:
	 */
	if (xfer->flags.stall_pipe) {
		struct usb_device *udev;
		struct usb_xfer_root *info;

		/* clear stall command */
		xfer->flags.stall_pipe = 0;

		/* get pointer to USB device */
		info = xfer->xroot;
		udev = info->udev;

		/*
		 * Only stall BULK and INTERRUPT endpoints.
		 */
		type = (ep->edesc->bmAttributes & UE_XFERTYPE);
		if ((type == UE_BULK) ||
		    (type == UE_INTERRUPT)) {
			uint8_t did_stall;

			did_stall = 1;

			if (udev->flags.usb_mode == USB_MODE_DEVICE) {
				(udev->bus->methods->set_stall) (
				    udev, ep, &did_stall);
			} else if (udev->ctrl_xfer[1]) {
				info = udev->ctrl_xfer[1]->xroot;
				usb_proc_msignal(
				    USB_BUS_CS_PROC(info->bus),
				    &udev->cs_msg[0], &udev->cs_msg[1]);
			} else {
				/* should not happen */
				DPRINTFN(0, "No stall handler\n");
			}
			/*
			 * Check if we should stall. Some USB hardware
			 * handles set- and clear-stall in hardware.
			 */
			if (did_stall) {
				/*
				 * The transfer will be continued when
				 * the clear-stall control endpoint
				 * message is received.
				 */
				ep->is_stalled = 1;
				return;
			}
		} else if (type == UE_ISOCHRONOUS) {

			/* 
			 * Make sure any FIFO overflow or other FIFO
			 * error conditions go away by resetting the
			 * endpoint FIFO through the clear stall
			 * method.
			 */
			if (udev->flags.usb_mode == USB_MODE_DEVICE) {
				(udev->bus->methods->clear_stall) (udev, ep);
			}
		}
	}
	/* Set or clear stall complete - special case */
	if (xfer->nframes == 0) {
		/* we are complete */
		xfer->aframes = 0;
		usbd_transfer_done(xfer, 0);
		return;
	}
	/*
	 * Handled cases:
	 *
	 * 1) Start the first transfer queued.
	 *
	 * 2) Re-start the current USB transfer.
	 */
	/*
	 * Check if there should be any
	 * pre transfer start delay:
	 */
	if (xfer->interval > 0) {
		type = (ep->edesc->bmAttributes & UE_XFERTYPE);
		if ((type == UE_BULK) ||
		    (type == UE_CONTROL)) {
			usbd_transfer_timeout_ms(xfer,
			    &usbd_transfer_start_cb,
			    xfer->interval);
			return;
		}
	}
	DPRINTF("start\n");

#if USB_HAVE_PF
	usbpf_xfertap(xfer, USBPF_XFERTAP_SUBMIT);
#endif
	/* the transfer can now be cancelled */
	xfer->flags_int.can_cancel_immed = 1;

	/* start USB transfer, if no error */
	if (xfer->error == 0)
		(ep->methods->start) (xfer);

	/* check for transfer error */
	if (xfer->error) {
		/* some error has happened */
		usbd_transfer_done(xfer, 0);
	}
}