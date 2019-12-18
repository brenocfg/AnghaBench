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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {TYPE_2__* xroot; } ;
struct TYPE_4__ {TYPE_1__* udev; } ;
struct TYPE_3__ {int /*<<< orphan*/  ctrlreq_cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*,int) ; 
 int USB_GET_STATE (struct usb_xfer*) ; 
#define  USB_ST_SETUP 128 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  usbd_transfer_submit (struct usb_xfer*) ; 

void
usbd_do_request_callback(struct usb_xfer *xfer, usb_error_t error)
{
	;				/* workaround for a bug in "indent" */

	DPRINTF("st=%u\n", USB_GET_STATE(xfer));

	switch (USB_GET_STATE(xfer)) {
	case USB_ST_SETUP:
		usbd_transfer_submit(xfer);
		break;
	default:
		cv_signal(&xfer->xroot->udev->ctrlreq_cv);
		break;
	}
}