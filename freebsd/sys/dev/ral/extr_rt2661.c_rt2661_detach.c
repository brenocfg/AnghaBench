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
struct rt2661_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  rxq; int /*<<< orphan*/  mgtq; int /*<<< orphan*/ * txq; int /*<<< orphan*/  sc_snd; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_LOCK (struct rt2661_softc*) ; 
 int /*<<< orphan*/  RAL_UNLOCK (struct rt2661_softc*) ; 
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_free_rx_ring (struct rt2661_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_free_tx_ring (struct rt2661_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2661_stop_locked (struct rt2661_softc*) ; 

int
rt2661_detach(void *xsc)
{
	struct rt2661_softc *sc = xsc;
	struct ieee80211com *ic = &sc->sc_ic;
	
	RAL_LOCK(sc);
	rt2661_stop_locked(sc);
	RAL_UNLOCK(sc);

	ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);

	rt2661_free_tx_ring(sc, &sc->txq[0]);
	rt2661_free_tx_ring(sc, &sc->txq[1]);
	rt2661_free_tx_ring(sc, &sc->txq[2]);
	rt2661_free_tx_ring(sc, &sc->txq[3]);
	rt2661_free_tx_ring(sc, &sc->mgtq);
	rt2661_free_rx_ring(sc, &sc->rxq);

	mtx_destroy(&sc->sc_mtx);

	return 0;
}