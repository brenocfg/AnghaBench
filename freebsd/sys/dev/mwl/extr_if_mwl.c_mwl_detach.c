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
struct ieee80211com {int dummy; } ;
struct mwl_softc {int /*<<< orphan*/  sc_snd; int /*<<< orphan*/  sc_mh; int /*<<< orphan*/  sc_watchdog; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MWL_LOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_RXFREE_DESTROY (struct mwl_softc*) ; 
 int /*<<< orphan*/  MWL_UNLOCK (struct mwl_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mwl_dma_cleanup (struct mwl_softc*) ; 
 int /*<<< orphan*/  mwl_hal_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwl_stop (struct mwl_softc*) ; 
 int /*<<< orphan*/  mwl_tx_cleanup (struct mwl_softc*) ; 

int
mwl_detach(struct mwl_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;

	MWL_LOCK(sc);
	mwl_stop(sc);
	MWL_UNLOCK(sc);
	/*
	 * NB: the order of these is important:
	 * o call the 802.11 layer before detaching the hal to
	 *   insure callbacks into the driver to delete global
	 *   key cache entries can be handled
	 * o reclaim the tx queue data structures after calling
	 *   the 802.11 layer as we'll get called back to reclaim
	 *   node state and potentially want to use them
	 * o to cleanup the tx queues the hal is called, so detach
	 *   it last
	 * Other than that, it's straightforward...
	 */
	ieee80211_ifdetach(ic);
	callout_drain(&sc->sc_watchdog);
	mwl_dma_cleanup(sc);
	MWL_RXFREE_DESTROY(sc);
	mwl_tx_cleanup(sc);
	mwl_hal_detach(sc->sc_mh);
	mbufq_drain(&sc->sc_snd);

	return 0;
}