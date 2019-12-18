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
struct rt2560_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  rxq; int /*<<< orphan*/  bcnq; int /*<<< orphan*/  prioq; int /*<<< orphan*/  atimq; int /*<<< orphan*/  txq; int /*<<< orphan*/  sc_snd; struct ieee80211com sc_ic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ieee80211_ifdetach (struct ieee80211com*) ; 
 int /*<<< orphan*/  mbufq_drain (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2560_free_rx_ring (struct rt2560_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2560_free_tx_ring (struct rt2560_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2560_stop (struct rt2560_softc*) ; 

int
rt2560_detach(void *xsc)
{
	struct rt2560_softc *sc = xsc;
	struct ieee80211com *ic = &sc->sc_ic;
	
	rt2560_stop(sc);

	ieee80211_ifdetach(ic);
	mbufq_drain(&sc->sc_snd);

	rt2560_free_tx_ring(sc, &sc->txq);
	rt2560_free_tx_ring(sc, &sc->atimq);
	rt2560_free_tx_ring(sc, &sc->prioq);
	rt2560_free_tx_ring(sc, &sc->bcnq);
	rt2560_free_rx_ring(sc, &sc->rxq);

	mtx_destroy(&sc->sc_mtx);

	return 0;
}