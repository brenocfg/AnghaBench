#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usb_error_t ;
struct TYPE_5__ {size_t curr_dma_set; int /*<<< orphan*/  control_act; scalar_t__ control_xfr; scalar_t__ control_hdr; } ;
struct usb_xfer {int aframes; int nframes; TYPE_2__ flags_int; int /*<<< orphan*/ * td_transfer_cache; int /*<<< orphan*/ * td_transfer_first; TYPE_3__** qh_start; TYPE_1__* xroot; int /*<<< orphan*/  endpoint; } ;
typedef  int /*<<< orphan*/  ehci_softc_t ;
struct TYPE_6__ {int /*<<< orphan*/  page_cache; } ;
typedef  TYPE_3__ ehci_qh_t ;
struct TYPE_4__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * EHCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_device_done (struct usb_xfer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ehci_dump_sqtds (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ehci_non_isoc_done_sub (struct usb_xfer*) ; 
 int ehcidebug ; 
 int /*<<< orphan*/  usb_pc_cpu_invalidate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ehci_non_isoc_done(struct usb_xfer *xfer)
{
	ehci_qh_t *qh;
	usb_error_t err = 0;

	DPRINTFN(13, "xfer=%p endpoint=%p transfer done\n",
	    xfer, xfer->endpoint);

#ifdef USB_DEBUG
	if (ehcidebug > 10) {
		ehci_softc_t *sc = EHCI_BUS2SC(xfer->xroot->bus);

		ehci_dump_sqtds(sc, xfer->td_transfer_first);
	}
#endif

	/* extract data toggle directly from the QH's overlay area */

	qh = xfer->qh_start[xfer->flags_int.curr_dma_set];

	usb_pc_cpu_invalidate(qh->page_cache);

	/* reset scanner */

	xfer->td_transfer_cache = xfer->td_transfer_first;

	if (xfer->flags_int.control_xfr) {

		if (xfer->flags_int.control_hdr) {

			err = ehci_non_isoc_done_sub(xfer);
		}
		xfer->aframes = 1;

		if (xfer->td_transfer_cache == NULL) {
			goto done;
		}
	}
	while (xfer->aframes != xfer->nframes) {

		err = ehci_non_isoc_done_sub(xfer);
		xfer->aframes++;

		if (xfer->td_transfer_cache == NULL) {
			goto done;
		}
	}

	if (xfer->flags_int.control_xfr &&
	    !xfer->flags_int.control_act) {

		err = ehci_non_isoc_done_sub(xfer);
	}
done:
	ehci_device_done(xfer, err);
}