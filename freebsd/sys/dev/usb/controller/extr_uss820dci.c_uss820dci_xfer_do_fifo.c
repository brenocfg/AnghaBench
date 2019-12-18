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
struct uss820dci_td {scalar_t__ remainder; struct uss820dci_td* obj_next; int /*<<< orphan*/  alt_next; scalar_t__ error; scalar_t__ (* func ) (struct uss820dci_softc*,struct uss820dci_td*) ;} ;
struct uss820dci_softc {int sc_xfer_complete; } ;
struct usb_xfer {void* td_transfer_last; struct uss820dci_td* td_transfer_cache; TYPE_1__* xroot; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 struct uss820dci_softc* USS820_DCI_BUS2SC (int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (struct uss820dci_softc*,struct uss820dci_td*) ; 

__attribute__((used)) static void
uss820dci_xfer_do_fifo(struct usb_xfer *xfer)
{
	struct uss820dci_softc *sc = USS820_DCI_BUS2SC(xfer->xroot->bus);
	struct uss820dci_td *td;

	DPRINTFN(9, "\n");

	td = xfer->td_transfer_cache;
	if (td == NULL)
		return;

	while (1) {
		if ((td->func) (sc, td)) {
			/* operation in progress */
			break;
		}
		if (((void *)td) == xfer->td_transfer_last) {
			goto done;
		}
		if (td->error) {
			goto done;
		} else if (td->remainder > 0) {
			/*
			 * We had a short transfer. If there is no alternate
			 * next, stop processing !
			 */
			if (!td->alt_next) {
				goto done;
			}
		}
		/*
		 * Fetch the next transfer descriptor.
		 */
		td = td->obj_next;
		xfer->td_transfer_cache = td;
	}
	return;

done:
	/* compute all actual lengths */
	xfer->td_transfer_cache = NULL;
	sc->sc_xfer_complete = 1;
}