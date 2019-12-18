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
typedef  size_t usb_stream_t ;
struct TYPE_3__ {int /*<<< orphan*/  bandwidth_reclaimed; } ;
struct usb_xfer {TYPE_1__ flags_int; } ;
struct usb_endpoint {TYPE_2__* endpoint_q; } ;
struct TYPE_4__ {int /*<<< orphan*/  head; struct usb_xfer* curr; } ;

/* Variables and functions */
 struct usb_xfer* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_transfer_insert (struct usb_xfer*) ; 

__attribute__((used)) static void
xhci_device_generic_multi_enter(struct usb_endpoint *ep,
    usb_stream_t stream_id, struct usb_xfer *enter_xfer)
{
	struct usb_xfer *xfer;

	/* check if there is a current transfer */
	xfer = ep->endpoint_q[stream_id].curr;
	if (xfer == NULL)
		return;

	/*
	 * Check if the current transfer is started and then pickup
	 * the next one, if any. Else wait for next start event due to
	 * block on failure feature.
	 */
	if (!xfer->flags_int.bandwidth_reclaimed)
		return;

	xfer = TAILQ_FIRST(&ep->endpoint_q[stream_id].head);
	if (xfer == NULL) {
		/*
		 * In case of enter we have to consider that the
		 * transfer is queued by the USB core after the enter
		 * method is called.
		 */
		xfer = enter_xfer;

		if (xfer == NULL)
			return;
	}

	/* try to multi buffer */
	xhci_transfer_insert(xfer);
}