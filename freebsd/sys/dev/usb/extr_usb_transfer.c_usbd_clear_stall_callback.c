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
typedef  int uint8_t ;
struct usb_xfer {int* frlengths; int nframes; int /*<<< orphan*/  error; int /*<<< orphan*/  frbuffers; TYPE_3__* endpoint; TYPE_1__* xroot; } ;
struct usb_device_request {int /*<<< orphan*/  wLength; int /*<<< orphan*/ * wIndex; int /*<<< orphan*/  wValue; int /*<<< orphan*/  bRequest; int /*<<< orphan*/  bmRequestType; } ;
typedef  int /*<<< orphan*/  req ;
struct TYPE_6__ {TYPE_2__* edesc; } ;
struct TYPE_5__ {int /*<<< orphan*/  bEndpointAddress; } ;
struct TYPE_4__ {int /*<<< orphan*/  udev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  UF_ENDPOINT_HALT ; 
 int /*<<< orphan*/  UR_CLEAR_FEATURE ; 
 int /*<<< orphan*/  USB_ERR_CANCELLED ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 129 
#define  USB_ST_TRANSFERRED 128 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USETW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UT_WRITE_ENDPOINT ; 
 int /*<<< orphan*/  usbd_clear_data_toggle (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  usbd_copy_in (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct usb_device_request*,int) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 

uint8_t
usbd_clear_stall_callback(struct usb_xfer *xfer1,
    struct usb_xfer *xfer2)
{
	struct usb_device_request req;

	if (xfer2 == NULL) {
		/* looks like we are tearing down */
		DPRINTF("NULL input parameter\n");
		return (0);
	}
	USB_XFER_LOCK_ASSERT(xfer1, MA_OWNED);
	USB_XFER_LOCK_ASSERT(xfer2, MA_OWNED);

	switch (USB_GET_STATE(xfer1)) {
	case USB_ST_SETUP:

		/*
		 * pre-clear the data toggle to DATA0 ("umass.c" and
		 * "ata-usb.c" depends on this)
		 */

		usbd_clear_data_toggle(xfer2->xroot->udev, xfer2->endpoint);

		/* setup a clear-stall packet */

		req.bmRequestType = UT_WRITE_ENDPOINT;
		req.bRequest = UR_CLEAR_FEATURE;
		USETW(req.wValue, UF_ENDPOINT_HALT);
		req.wIndex[0] = xfer2->endpoint->edesc->bEndpointAddress;
		req.wIndex[1] = 0;
		USETW(req.wLength, 0);

		/*
		 * "usbd_transfer_setup_sub()" will ensure that
		 * we have sufficient room in the buffer for
		 * the request structure!
		 */

		/* copy in the transfer */

		usbd_copy_in(xfer1->frbuffers, 0, &req, sizeof(req));

		/* set length */
		xfer1->frlengths[0] = sizeof(req);
		xfer1->nframes = 1;

		usbd_transfer_submit(xfer1);
		return (0);

	case USB_ST_TRANSFERRED:
		break;

	default:			/* Error */
		if (xfer1->error == USB_ERR_CANCELLED) {
			return (0);
		}
		break;
	}
	return (1);			/* Clear Stall Finished */
}