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
struct TYPE_6__ {int can_cancel_immed; } ;
struct usb_xfer {scalar_t__ error; TYPE_3__ flags_int; TYPE_2__* xroot; struct usb_endpoint* endpoint; } ;
struct usb_endpoint {TYPE_1__* methods; } ;
struct TYPE_5__ {int /*<<< orphan*/  bus; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start ) (struct usb_xfer*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USBPF_XFERTAP_SUBMIT ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbpf_xfertap (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
usbd_transfer_start_cb(void *arg)
{
	struct usb_xfer *xfer = arg;
	struct usb_endpoint *ep = xfer->endpoint;

	USB_BUS_LOCK_ASSERT(xfer->xroot->bus, MA_OWNED);

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