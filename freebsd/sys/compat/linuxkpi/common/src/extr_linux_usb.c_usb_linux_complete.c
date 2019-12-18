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
struct usb_xfer {int dummy; } ;
struct urb {int /*<<< orphan*/  (* complete ) (struct urb*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct urb*) ; 
 struct urb* usbd_xfer_get_priv (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_xfer_set_priv (struct usb_xfer*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
usb_linux_complete(struct usb_xfer *xfer)
{
	struct urb *urb;

	urb = usbd_xfer_get_priv(xfer);
	usbd_xfer_set_priv(xfer, NULL);
	if (urb->complete) {
		(urb->complete) (urb);
	}
}