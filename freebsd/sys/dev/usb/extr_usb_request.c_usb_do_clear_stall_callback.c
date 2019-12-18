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
typedef  size_t usb_stream_t ;
typedef  int /*<<< orphan*/  usb_error_t ;
typedef  int uint8_t ;
struct usb_xfer {int nframes; int /*<<< orphan*/  frbuffers; TYPE_1__* xroot; } ;
struct usb_endpoint {TYPE_2__* edesc; int /*<<< orphan*/  is_stalled; TYPE_3__* endpoint_q; int /*<<< orphan*/  toggle_next; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/ * wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
struct usb_device {int endpoints_max; int /*<<< orphan*/  bus; struct usb_endpoint* ep_curr; int /*<<< orphan*/  clear_stall_errors; struct usb_endpoint* endpoints; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_6__ {int /*<<< orphan*/  curr; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_4__ {struct usb_device* udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  UF_ENDPOINT_HALT ; 
 int /*<<< orphan*/  UR_CLEAR_FEATURE ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_CS_RESET_LIMIT ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int /*<<< orphan*/  USB_ERR_TIMEOUT ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
 size_t USB_MAX_EP_STREAMS ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_ENDPOINT ; 
 int /*<<< orphan*/  usb_command_wrapper (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_no_cs_fail ; 
 int /*<<< orphan*/  usbd_clear_stall_locked (struct usb_device*,struct usb_endpoint*) ; 
 int /*<<< orphan*/  usbd_copy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_start_re_enumerate (struct usb_device*) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 

void
usb_do_clear_stall_callback(struct usb_xfer *xfer, usb_error_t error)
{
	struct usb_device_request req;
	struct usb_device *udev;
	struct usb_endpoint *ep;
	struct usb_endpoint *ep_end;
	struct usb_endpoint *ep_first;
	usb_stream_t x;
	uint8_t to;

	udev = xfer->xroot->udev;

	USB_BUS_LOCK(udev->bus);

	/* round robin endpoint clear stall */

	ep = udev->ep_curr;
	ep_end = udev->endpoints + udev->endpoints_max;
	ep_first = udev->endpoints;
	to = udev->endpoints_max;

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_TRANSFERRED:
tr_transferred:
		/* reset error counter */
		udev->clear_stall_errors = 0;

		if (ep == NULL)
			goto tr_setup;		/* device was unconfigured */
		if (ep->edesc &&
		    ep->is_stalled) {
			ep->toggle_next = 0;
			ep->is_stalled = 0;
			/* some hardware needs a callback to clear the data toggle */
			usbd_clear_stall_locked(udev, ep);
			for (x = 0; x != USB_MAX_EP_STREAMS; x++) {
				/* start the current or next transfer, if any */
				usb_command_wrapper(&ep->endpoint_q[x],
				    ep->endpoint_q[x].curr);
			}
		}
		ep++;

	case USB_ST_SETUP:
tr_setup:
		if (to == 0)
			break;			/* no endpoints - nothing to do */
		if ((ep < ep_first) || (ep >= ep_end))
			ep = ep_first;	/* endpoint wrapped around */
		if (ep->edesc &&
		    ep->is_stalled) {

			/* setup a clear-stall packet */

			req.bmRequestType = UT_WRITE_ENDPOINT;
			req.bRequest = UR_CLEAR_FEATURE;
			USETW(req.wValue, UF_ENDPOINT_HALT);
			req.wIndex[0] = ep->edesc->bEndpointAddress;
			req.wIndex[1] = 0;
			USETW(req.wLength, 0);

			/* copy in the transfer */

			usbd_copy_in(xfer->frbuffers, 0, &req, sizeof(req));

			/* set length */
			usbd_xfer_set_frame_len(xfer, 0, sizeof(req));
			xfer->nframes = 1;
			USB_BUS_UNLOCK(udev->bus);

			usbd_transfer_submit(xfer);

			USB_BUS_LOCK(udev->bus);
			break;
		}
		ep++;
		to--;
		goto tr_setup;

	default:
		if (error == USB_ERR_CANCELLED)
			break;

		DPRINTF("Clear stall failed.\n");

		/*
		 * Some VMs like VirtualBox always return failure on
		 * clear-stall which we sometimes should just ignore.
		 */
		if (usb_no_cs_fail)
			goto tr_transferred;
		if (udev->clear_stall_errors == USB_CS_RESET_LIMIT)
			goto tr_setup;

		if (error == USB_ERR_TIMEOUT) {
			udev->clear_stall_errors = USB_CS_RESET_LIMIT;
			DPRINTF("Trying to re-enumerate.\n");
			usbd_start_re_enumerate(udev);
		} else {
			udev->clear_stall_errors++;
			if (udev->clear_stall_errors == USB_CS_RESET_LIMIT) {
				DPRINTF("Trying to re-enumerate.\n");
				usbd_start_re_enumerate(udev);
			}
		}
		goto tr_setup;
	}

	/* store current endpoint */
	udev->ep_curr = ep;
	USB_BUS_UNLOCK(udev->bus);
}