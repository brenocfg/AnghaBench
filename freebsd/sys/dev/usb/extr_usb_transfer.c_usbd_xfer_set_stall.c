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
struct TYPE_3__ {int stall_pipe; } ;
struct usb_xfer {TYPE_2__* xroot; TYPE_1__ flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_BUS_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USB_XFER_LOCK_ASSERT (struct usb_xfer*,int /*<<< orphan*/ ) ; 

void
usbd_xfer_set_stall(struct usb_xfer *xfer)
{
	if (xfer == NULL) {
		/* tearing down */
		return;
	}
	USB_XFER_LOCK_ASSERT(xfer, MA_OWNED);

	/* avoid any races by locking the USB mutex */
	USB_BUS_LOCK(xfer->xroot->bus);
	xfer->flags.stall_pipe = 1;
	USB_BUS_UNLOCK(xfer->xroot->bus);
}