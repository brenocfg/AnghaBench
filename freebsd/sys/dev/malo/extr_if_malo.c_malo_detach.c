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
struct malo_softc {int /*<<< orphan*/  malo_snd; int /*<<< orphan*/  malo_mh; int /*<<< orphan*/  malo_watchdog_timer; int /*<<< orphan*/ * malo_tq; int /*<<< orphan*/  malo_txtask; int /*<<< orphan*/  malo_rxtask; struct ieee80211com malo_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MALO_LOCK_DESTROY (struct malo_softc*) ; 
 int /*<<< orphan*/  callout_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  malo_dma_cleanup (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_hal_detach (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  malo_stop (struct malo_softc*) ; 
 int /*<<< orphan*/  malo_tx_cleanup (struct malo_softc*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_drain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskqueue_free (int /*<<< orphan*/ *) ; 

int
malo_detach(struct malo_softc *sc)
{
	struct ieee80211com *ic = &sc->malo_ic;

	malo_stop(sc);

	if (sc->malo_tq != NULL) {
		taskqueue_drain(sc->malo_tq, &sc->malo_rxtask);
		taskqueue_drain(sc->malo_tq, &sc->malo_txtask);
		taskqueue_free(sc->malo_tq);
		sc->malo_tq = NULL;
	}

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
	callout_drain(&sc->malo_watchdog_timer);
	malo_dma_cleanup(sc);
	malo_tx_cleanup(sc);
	malo_hal_detach(sc->malo_mh);
	mbufq_drain(&sc->malo_snd);
	MALO_LOCK_DESTROY(sc);

	return 0;
}