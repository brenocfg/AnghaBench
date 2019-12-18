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
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_5__ {int manual_status; scalar_t__ force_short_xfer; } ;
struct TYPE_4__ {int control_rem; } ;
struct usb_xfer {int nframes; TYPE_2__ flags; int /*<<< orphan*/  error; TYPE_1__ flags_int; TYPE_3__* xroot; } ;
struct usb_device_request {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  USB_ERR_BAD_CONTEXT ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  usb_handle_request (struct usb_xfer*) ; 
 int /*<<< orphan*/  usb_needs_explore (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_frame_len (struct usb_xfer*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  usbd_xfer_set_stall (struct usb_xfer*) ; 

void
usb_handle_request_callback(struct usb_xfer *xfer, usb_error_t error)
{
	usb_error_t err;

	/* check the current transfer state */

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_SETUP:
	case USB_ST_TRANSFERRED:

		/* handle the request */
		err = usb_handle_request(xfer);

		if (err) {

			if (err == USB_ERR_BAD_CONTEXT) {
				/* we need to re-setup the control transfer */
				usb_needs_explore(xfer->xroot->bus, 0);
				break;
			}
			goto tr_restart;
		}
		usbd_transfer_submit(xfer);
		break;

	default:
		/* check if a control transfer is active */
		if (xfer->flags_int.control_rem != 0xFFFF) {
			/* handle the request */
			err = usb_handle_request(xfer);
		}
		if (xfer->error != USB_ERR_CANCELLED) {
			/* should not happen - try stalling */
			goto tr_restart;
		}
		break;
	}
	return;

tr_restart:
	/*
	 * If a control transfer is active, stall it, and wait for the
	 * next control transfer.
	 */
	usbd_xfer_set_frame_len(xfer, 0, sizeof(struct usb_device_request));
	xfer->nframes = 1;
	xfer->flags.manual_status = 1;
	xfer->flags.force_short_xfer = 0;
	usbd_xfer_set_stall(xfer);	/* cancel previous transfer, if any */
	usbd_transfer_submit(xfer);
}