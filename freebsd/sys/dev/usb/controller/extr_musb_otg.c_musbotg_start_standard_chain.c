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
struct usb_xfer {scalar_t__ timeout; TYPE_2__* xroot; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 int /*<<< orphan*/  musbotg_timeout ; 
 scalar_t__ musbotg_xfer_do_fifo (struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_enqueue (int /*<<< orphan*/ *,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_timeout_ms (struct usb_xfer*,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void
musbotg_start_standard_chain(struct usb_xfer *xfer)
{
	DPRINTFN(8, "\n");

	/* poll one time */
	if (musbotg_xfer_do_fifo(xfer)) {

		DPRINTFN(14, "enabled interrupts on endpoint\n");

		/* put transfer on interrupt queue */
		usbd_transfer_enqueue(&xfer->xroot->bus->intr_q, xfer);

		/* start timeout, if any */
		if (xfer->timeout != 0) {
			usbd_transfer_timeout_ms(xfer,
			    &musbotg_timeout, xfer->timeout);
		}
	}
}