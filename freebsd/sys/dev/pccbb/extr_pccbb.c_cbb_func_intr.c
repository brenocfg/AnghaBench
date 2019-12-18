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
struct cbb_softc {scalar_t__ cardok; } ;
struct cbb_intrhand {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* intr ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * filt; struct cbb_softc* sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  CBB_CARD_PRESENT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CBB_SOCKET_STATE ; 
 int /*<<< orphan*/  cbb_get (struct cbb_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cbb_func_intr(void *arg)
{
	struct cbb_intrhand *ih = (struct cbb_intrhand *)arg;
	struct cbb_softc *sc = ih->sc;

	/*
	 * While this check may seem redundant, it helps close a race
	 * condition.  If the card is ejected after the filter runs, but
	 * before this ISR can be scheduled, then we need to do the same
	 * filtering to prevent the card's ISR from being called.  One could
	 * argue that the card's ISR should be able to cope, but experience
	 * has shown they can't always.  This mitigates the problem by making
	 * the race quite a bit smaller.  Properly written client ISRs should
	 * cope with the card going away in the middle of the ISR.  We assume
	 * that drivers that are sophisticated enough to use filters don't
	 * need our protection.  This also allows us to ensure they *ARE*
	 * called if their filter said they needed to be called.
	 */
	if (ih->filt == NULL) {
		if (!sc->cardok)
			return;
		if (!CBB_CARD_PRESENT(cbb_get(sc, CBB_SOCKET_STATE))) {
			sc->cardok = 0;
			return;
		}
	}

	/*
	 * Call the registered ithread interrupt handler.  This entire routine
	 * will be called with Giant if this isn't an MP safe driver, or not
	 * if it is.  Either way, we don't have to worry.
	 */
	ih->intr(ih->arg);
}