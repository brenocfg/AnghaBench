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
struct rt2860_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  rxq; int /*<<< orphan*/ * txq; int /*<<< orphan*/  sc_snd; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct rt2860_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2860_softc*) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_free_rx_ring (struct rt2860_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_free_tx_pool (struct rt2860_softc*) ; 
 int /*<<< orphan*/  rt2860_free_tx_ring (struct rt2860_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_stop_locked (struct rt2860_softc*) ; 

int
rt2860_detach(void *xsc)
{
	struct rt2860_softc *sc = xsc;
	struct ieee80211com *ic = &sc->sc_ic;
	int qid;

	RAL_LOCK(sc);
	rt2860_stop_locked(sc);
	RAL_UNLOCK(sc);

	ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);
	for (qid = 0; qid < 6; qid++)
		rt2860_free_tx_ring(sc, &sc->txq[qid]);
	rt2860_free_rx_ring(sc, &sc->rxq);
	rt2860_free_tx_pool(sc);

	mtx_destroy(&sc->sc_mtx);

	return 0;
}