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
struct usb_xfer {scalar_t__ timeout; TYPE_2__* xroot; int /*<<< orphan*/  stream_id; int /*<<< orphan*/  endpoint; } ;
struct TYPE_4__ {TYPE_1__* bus; } ;
struct TYPE_3__ {int /*<<< orphan*/  intr_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  usbd_transfer_enqueue (int /*<<< orphan*/ *,struct usb_xfer*) ; 
 int /*<<< orphan*/  usbd_transfer_timeout_ms (struct usb_xfer*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  xhci_device_generic_multi_enter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_timeout ; 
 int /*<<< orphan*/  xhci_transfer_insert (struct usb_xfer*) ; 

__attribute__((used)) static void
xhci_device_generic_start(struct usb_xfer *xfer)
{
	DPRINTF("\n");

	/* try to insert xfer on HW queue */
	xhci_transfer_insert(xfer);

	/* try to multi buffer */
	xhci_device_generic_multi_enter(xfer->endpoint,
	    xfer->stream_id, NULL);

	/* add transfer last on interrupt queue */
	usbd_transfer_enqueue(&xfer->xroot->bus->intr_q, xfer);

	/* start timeout, if any */
	if (xfer->timeout != 0)
		usbd_transfer_timeout_ms(xfer, &xhci_timeout, xfer->timeout);
}