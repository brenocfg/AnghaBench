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
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_2__ {int /*<<< orphan*/  control_act; scalar_t__ control_xfr; scalar_t__ control_hdr; } ;
struct usb_xfer {int aframes; int nframes; TYPE_1__ flags_int; int /*<<< orphan*/ * td_transfer_cache; int /*<<< orphan*/ * td_transfer_first; int /*<<< orphan*/  endpoint; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_device_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uhci_dump_tds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uhci_non_isoc_done_sub (struct usb_xfer*) ; 
 int uhcidebug ; 
 int /*<<< orphan*/  usb_bdma_post_sync (struct usb_xfer*) ; 

__attribute__((used)) static void
uhci_non_isoc_done(struct usb_xfer *xfer)
{
	usb_error_t err = 0;

	DPRINTFN(13, "xfer=%p endpoint=%p transfer done\n",
	    xfer, xfer->endpoint);

#ifdef USB_DEBUG
	if (uhcidebug > 10) {
		uhci_dump_tds(xfer->td_transfer_first);
	}
#endif

	/* sync any DMA memory before doing fixups */

	usb_bdma_post_sync(xfer);

	/* reset scanner */

	xfer->td_transfer_cache = xfer->td_transfer_first;

	if (xfer->flags_int.control_xfr) {
		if (xfer->flags_int.control_hdr) {

			err = uhci_non_isoc_done_sub(xfer);
		}
		xfer->aframes = 1;

		if (xfer->td_transfer_cache == NULL) {
			goto done;
		}
	}
	while (xfer->aframes != xfer->nframes) {

		err = uhci_non_isoc_done_sub(xfer);
		xfer->aframes++;

		if (xfer->td_transfer_cache == NULL) {
			goto done;
		}
	}

	if (xfer->flags_int.control_xfr &&
	    !xfer->flags_int.control_act) {

		err = uhci_non_isoc_done_sub(xfer);
	}
done:
	uhci_device_done(xfer, err);
}