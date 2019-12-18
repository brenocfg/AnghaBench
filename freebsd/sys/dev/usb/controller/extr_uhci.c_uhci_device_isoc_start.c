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

/* Variables and functions */
 int /*<<< orphan*/  uhci_transfer_intr_enqueue (struct usb_xfer*) ; 

__attribute__((used)) static void
uhci_device_isoc_start(struct usb_xfer *xfer)
{
	/* put transfer on interrupt queue */
	uhci_transfer_intr_enqueue(xfer);
}