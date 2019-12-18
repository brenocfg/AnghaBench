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
typedef  int uint32_t ;
struct rt2860_softc {int sc_flags; int /*<<< orphan*/  rxq; int /*<<< orphan*/ * txq; scalar_t__ qfullmsk; scalar_t__ sc_tx_timer; int /*<<< orphan*/  watchdog_ch; } ;

/* Variables and functions */
 int /*<<< orphan*/  RAL_BARRIER_WRITE (struct rt2860_softc*) ; 
 int RAL_READ (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2860_softc*,int /*<<< orphan*/ ,int) ; 
 int RT2860_BBP_HRST ; 
 int /*<<< orphan*/  RT2860_INT_MASK ; 
 int RT2860_MAC_RX_EN ; 
 int RT2860_MAC_SRST ; 
 int /*<<< orphan*/  RT2860_MAC_SYS_CTRL ; 
 int RT2860_MAC_TX_EN ; 
 int RT2860_RUNNING ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_reset_rx_ring (struct rt2860_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_reset_tx_ring (struct rt2860_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rt2860_set_gp_timer (struct rt2860_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2860_set_leds (struct rt2860_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
rt2860_stop_locked(struct rt2860_softc *sc)
{
	uint32_t tmp;
	int qid;

	if (sc->sc_flags & RT2860_RUNNING)
		rt2860_set_leds(sc, 0);	/* turn all LEDs off */

	callout_stop(&sc->watchdog_ch);
	sc->sc_tx_timer = 0;
	sc->sc_flags &= ~RT2860_RUNNING;

	/* disable interrupts */
	RAL_WRITE(sc, RT2860_INT_MASK, 0);

	/* disable GP timer */
	rt2860_set_gp_timer(sc, 0);

	/* disable Rx */
	tmp = RAL_READ(sc, RT2860_MAC_SYS_CTRL);
	tmp &= ~(RT2860_MAC_RX_EN | RT2860_MAC_TX_EN);
	RAL_WRITE(sc, RT2860_MAC_SYS_CTRL, tmp);

	/* reset adapter */
	RAL_WRITE(sc, RT2860_MAC_SYS_CTRL, RT2860_BBP_HRST | RT2860_MAC_SRST);
	RAL_BARRIER_WRITE(sc);
	RAL_WRITE(sc, RT2860_MAC_SYS_CTRL, 0);

	/* reset Tx and Rx rings (and reclaim TXWIs) */
	sc->qfullmsk = 0;
	for (qid = 0; qid < 6; qid++)
		rt2860_reset_tx_ring(sc, &sc->txq[qid]);
	rt2860_reset_rx_ring(sc, &sc->rxq);
}