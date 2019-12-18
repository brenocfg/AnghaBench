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
typedef  int uint8_t ;
struct usb_xfer {void* td_transfer_last; struct musbotg_td* td_transfer_cache; TYPE_1__* xroot; } ;
struct musbotg_td {scalar_t__ remainder; struct musbotg_td* obj_next; int /*<<< orphan*/  alt_next; scalar_t__ error; scalar_t__ (* func ) (struct musbotg_td*) ;} ;
struct musbotg_softc {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINTFN (int,char*) ; 
 struct musbotg_softc* MUSBOTG_BUS2SC (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musbotg_standard_done (struct usb_xfer*) ; 
 scalar_t__ stub1 (struct musbotg_td*) ; 

__attribute__((used)) static uint8_t
musbotg_xfer_do_fifo(struct usb_xfer *xfer)
{
	struct musbotg_softc *sc;
	struct musbotg_td *td;

	DPRINTFN(8, "\n");
	sc = MUSBOTG_BUS2SC(xfer->xroot->bus);

	td = xfer->td_transfer_cache;
	while (1) {

		if ((td->func) (td)) {
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
		 * Fetch the next transfer descriptor and transfer
		 * some flags to the next transfer descriptor
		 */
		td = td->obj_next;
		xfer->td_transfer_cache = td;
	}

	return (1);			/* not complete */
done:
	/* compute all actual lengths */
	musbotg_standard_done(xfer);

	return (0);			/* complete */
}