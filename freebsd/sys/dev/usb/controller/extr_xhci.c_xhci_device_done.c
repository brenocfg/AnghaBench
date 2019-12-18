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
typedef  int /*<<< orphan*/  usb_error_t ;
struct usb_xfer {int /*<<< orphan*/  endpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usbd_transfer_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xhci_transfer_remove (struct usb_xfer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
xhci_device_done(struct usb_xfer *xfer, usb_error_t error)
{
	DPRINTFN(2, "xfer=%p, endpoint=%p, error=%d\n",
	    xfer, xfer->endpoint, error);

	/* remove transfer from HW queue */
	xhci_transfer_remove(xfer, error);

	/* dequeue transfer and start next transfer */
	usbd_transfer_done(xfer, error);
}