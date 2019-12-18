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
struct TYPE_2__ {scalar_t__ can_cancel_immed; } ;
struct usb_xfer {int timeout; TYPE_1__ flags_int; } ;

/* Variables and functions */
 int /*<<< orphan*/  ehci_transfer_intr_enqueue (struct usb_xfer*) ; 

__attribute__((used)) static void
ehci_device_isoc_fs_start(struct usb_xfer *xfer)
{
	/*
	 * We don't allow cancelling of the SPLIT transaction USB FULL
	 * speed transfer, because it disturbs the bandwidth
	 * computation algorithm.
	 */
	xfer->flags_int.can_cancel_immed = 0;

	/* set a default timeout */
	if (xfer->timeout == 0)
		xfer->timeout = 500; /* ms */

	/* put transfer on interrupt queue */
	ehci_transfer_intr_enqueue(xfer);
}