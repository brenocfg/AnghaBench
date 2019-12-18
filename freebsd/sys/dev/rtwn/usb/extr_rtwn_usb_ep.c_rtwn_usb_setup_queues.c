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
struct rtwn_softc {int page_count; int npubqpages; int nhqpages; int nnqpages; int nlqpages; } ;
struct rtwn_usb_softc {int ntx; struct rtwn_softc uc_sc; } ;

/* Variables and functions */

__attribute__((used)) static void
rtwn_usb_setup_queues(struct rtwn_usb_softc *uc)
{
	struct rtwn_softc *sc = &uc->uc_sc;
	int hasnq, haslq, nqueues, nqpages, nrempages;

	/* Get Tx queues to USB endpoints mapping. */
	hasnq = haslq = 0;
	switch (uc->ntx) {
	case 4:
	case 3:
		haslq = 1;
		/* FALLTHROUGH */
	case 2:
		hasnq = 1;
		/* FALLTHROUGH */
	default:
		break;
	}
	nqueues = 1 + hasnq + haslq;

	/* Get the number of pages for each queue. */
	nqpages = (sc->page_count - sc->npubqpages) / nqueues;

	/*
	 * The remaining pages are assigned to the high priority
	 * queue.
	 */
	nrempages = (sc->page_count - sc->npubqpages) % nqueues;

	sc->nhqpages = nqpages + nrempages;
	sc->nnqpages = (hasnq ? nqpages : 0);
	sc->nlqpages = (haslq ? nqpages : 0);
}