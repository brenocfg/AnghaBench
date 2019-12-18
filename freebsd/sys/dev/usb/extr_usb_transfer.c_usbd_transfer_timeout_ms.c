#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_timeout_t ;
struct usb_xfer {int /*<<< orphan*/  timeout_handle; TYPE_1__* xroot; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  USB_BUS_LOCK_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ USB_CALLOUT_ZERO_TICKS ; 
 scalar_t__ USB_MS_TO_TICKS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_callout_reset (int /*<<< orphan*/ *,scalar_t__,void (*) (void*),struct usb_xfer*) ; 

void
usbd_transfer_timeout_ms(struct usb_xfer *xfer,
    void (*cb) (void *arg), usb_timeout_t ms)
{
	USB_BUS_LOCK_ASSERT(xfer->xroot->bus, MA_OWNED);

	/* defer delay */
	usb_callout_reset(&xfer->timeout_handle,
	    USB_MS_TO_TICKS(ms) + USB_CALLOUT_ZERO_TICKS, cb, xfer);
}