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
typedef  int /*<<< orphan*/  uint8_t ;
struct usb_xfer {void* td_transfer_last; struct saf1761_otg_td* td_transfer_cache; } ;
struct saf1761_otg_td {scalar_t__ remainder; int /*<<< orphan*/  toggle; struct saf1761_otg_td* obj_next; int /*<<< orphan*/  alt_next; scalar_t__ error_any; scalar_t__ (* func ) (struct saf1761_otg_softc*,struct saf1761_otg_td*) ;} ;
struct saf1761_otg_softc {int sc_xfer_complete; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 scalar_t__ stub1 (struct saf1761_otg_softc*,struct saf1761_otg_td*) ; 

__attribute__((used)) static void
saf1761_otg_xfer_do_fifo(struct saf1761_otg_softc *sc, struct usb_xfer *xfer)
{
	struct saf1761_otg_td *td;
	uint8_t toggle;

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
		if (td->error_any) {
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
		toggle = td->toggle;
		td = td->obj_next;
		td->toggle = toggle;
		xfer->td_transfer_cache = td;
	}
	return;

done:
	/* compute all actual lengths */
	xfer->td_transfer_cache = NULL;
	sc->sc_xfer_complete = 1;
}