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
typedef  int uint32_t ;
struct uss820dci_softc {int /*<<< orphan*/  sc_bus; } ;
struct usb_xfer {int nframes; TYPE_2__* endpoint; scalar_t__ isoc_time_complete; TYPE_1__* xroot; } ;
struct TYPE_4__ {int isoc_next; int is_synced; } ;
struct TYPE_3__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*,...) ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 int USS820_READ_1 (struct uss820dci_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  USS820_SOFL ; 
 int USS820_SOFL_MASK ; 
 scalar_t__ usb_isoc_time_expand (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  uss820dci_setup_standard_chain (struct usb_xfer*) ; 

__attribute__((used)) static void
uss820dci_device_isoc_fs_enter(struct usb_xfer *xfer)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(xfer->xroot->bus);
	uint32_t temp;
	uint32_t nframes;

	DPRINTFN(6, "xfer=%p next=%d nframes=%d\n",
	    xfer, xfer->endpoint->isoc_next, xfer->nframes);

	/* get the current frame index - we don't need the high bits */

	nframes = USS820_READ_1(sc, USS820_SOFL);

	/*
	 * check if the frame index is within the window where the
	 * frames will be inserted
	 */
	temp = (nframes - xfer->endpoint->isoc_next) & USS820_SOFL_MASK;

	if ((xfer->endpoint->is_synced == 0) ||
	    (temp < xfer->nframes)) {
		/*
		 * If there is data underflow or the pipe queue is
		 * empty we schedule the transfer a few frames ahead
		 * of the current frame position. Else two isochronous
		 * transfers might overlap.
		 */
		xfer->endpoint->isoc_next = (nframes + 3) & USS820_SOFL_MASK;
		xfer->endpoint->is_synced = 1;
		DPRINTFN(3, "start next=%d\n", xfer->endpoint->isoc_next);
	}
	/*
	 * compute how many milliseconds the insertion is ahead of the
	 * current frame position:
	 */
	temp = (xfer->endpoint->isoc_next - nframes) & USS820_SOFL_MASK;

	/*
	 * pre-compute when the isochronous transfer will be finished:
	 */
	xfer->isoc_time_complete =
	    usb_isoc_time_expand(&sc->sc_bus, nframes) + temp +
	    xfer->nframes;

	/* compute frame number for next insertion */
	xfer->endpoint->isoc_next += xfer->nframes;

	/* setup TDs */
	uss820dci_setup_standard_chain(xfer);
}