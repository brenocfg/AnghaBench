#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_12__ {int physaddr; } ;
struct TYPE_11__ {int physaddr; } ;
struct TYPE_10__ {int physaddr; } ;
struct TYPE_9__ {int physaddr; } ;
struct TYPE_8__ {int physaddr; } ;
struct ieee80211com {scalar_t__ ic_opmode; scalar_t__ ic_promisc; int /*<<< orphan*/  ic_curchan; int /*<<< orphan*/  ic_macaddr; int /*<<< orphan*/  ic_vaps; } ;
struct rt2560_softc {int /*<<< orphan*/  watchdog_ch; int /*<<< orphan*/  sc_flags; int /*<<< orphan*/  rx_ant; int /*<<< orphan*/  tx_ant; TYPE_5__ rxq; TYPE_4__ bcnq; TYPE_3__ atimq; TYPE_2__ prioq; TYPE_1__ txq; struct ieee80211com sc_ic; } ;
struct ieee80211vap {int /*<<< orphan*/  iv_myaddr; } ;
struct TYPE_13__ {int val; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 scalar_t__ IEEE80211_M_HOSTAP ; 
 scalar_t__ IEEE80211_M_MBSS ; 
 scalar_t__ IEEE80211_M_MONITOR ; 
 int /*<<< orphan*/  RAL_LOCK_ASSERT (struct rt2560_softc*) ; 
 int /*<<< orphan*/  RAL_READ (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RAL_WRITE (struct rt2560_softc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RT2560_ARSP_PLCP_1 ; 
 int RT2560_ATIM_RING_COUNT ; 
 int /*<<< orphan*/  RT2560_CNT0 ; 
 int /*<<< orphan*/  RT2560_CNT4 ; 
 int /*<<< orphan*/  RT2560_CSR1 ; 
 int /*<<< orphan*/  RT2560_CSR7 ; 
 int /*<<< orphan*/  RT2560_CSR8 ; 
 int RT2560_DROP_CRC_ERROR ; 
 int RT2560_DROP_CTL ; 
 int RT2560_DROP_NOT_TO_ME ; 
 int RT2560_DROP_PHY_ERROR ; 
 int RT2560_DROP_TODS ; 
 int RT2560_DROP_VERSION_ERROR ; 
 int /*<<< orphan*/  RT2560_F_RUNNING ; 
 int RT2560_HOST_READY ; 
 int RT2560_INTR_MASK ; 
 int RT2560_PRIO_RING_COUNT ; 
 int RT2560_RESET_ASIC ; 
 int /*<<< orphan*/  RT2560_RXCSR0 ; 
 int /*<<< orphan*/  RT2560_RXCSR1 ; 
 int /*<<< orphan*/  RT2560_RXCSR2 ; 
 int RT2560_RX_DESC_SIZE ; 
 int RT2560_RX_RING_COUNT ; 
 int /*<<< orphan*/  RT2560_TXCSR2 ; 
 int /*<<< orphan*/  RT2560_TXCSR3 ; 
 int /*<<< orphan*/  RT2560_TXCSR4 ; 
 int /*<<< orphan*/  RT2560_TXCSR5 ; 
 int /*<<< orphan*/  RT2560_TXCSR6 ; 
 int RT2560_TX_DESC_SIZE ; 
 int RT2560_TX_RING_COUNT ; 
 struct ieee80211vap* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_reset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct rt2560_softc*) ; 
 int /*<<< orphan*/  hz ; 
 int nitems (TYPE_6__*) ; 
 scalar_t__ rt2560_bbp_init (struct rt2560_softc*) ; 
 TYPE_6__* rt2560_def_mac ; 
 int /*<<< orphan*/  rt2560_set_chan (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_set_macaddr (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_set_rxantenna (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_set_txantenna (struct rt2560_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_stop_locked (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_update_led (struct rt2560_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rt2560_update_plcp (struct rt2560_softc*) ; 
 int /*<<< orphan*/  rt2560_update_slot (struct ieee80211com*) ; 
 int /*<<< orphan*/  rt2560_watchdog ; 

__attribute__((used)) static void
rt2560_init_locked(struct rt2560_softc *sc)
{
	struct ieee80211com *ic = &sc->sc_ic;
	struct ieee80211vap *vap = TAILQ_FIRST(&ic->ic_vaps);
	uint32_t tmp;
	int i;

	RAL_LOCK_ASSERT(sc);

	rt2560_stop_locked(sc);

	/* setup tx rings */
	tmp = RT2560_PRIO_RING_COUNT << 24 |
	      RT2560_ATIM_RING_COUNT << 16 |
	      RT2560_TX_RING_COUNT   <<  8 |
	      RT2560_TX_DESC_SIZE;

	/* rings must be initialized in this exact order */
	RAL_WRITE(sc, RT2560_TXCSR2, tmp);
	RAL_WRITE(sc, RT2560_TXCSR3, sc->txq.physaddr);
	RAL_WRITE(sc, RT2560_TXCSR5, sc->prioq.physaddr);
	RAL_WRITE(sc, RT2560_TXCSR4, sc->atimq.physaddr);
	RAL_WRITE(sc, RT2560_TXCSR6, sc->bcnq.physaddr);

	/* setup rx ring */
	tmp = RT2560_RX_RING_COUNT << 8 | RT2560_RX_DESC_SIZE;

	RAL_WRITE(sc, RT2560_RXCSR1, tmp);
	RAL_WRITE(sc, RT2560_RXCSR2, sc->rxq.physaddr);

	/* initialize MAC registers to default values */
	for (i = 0; i < nitems(rt2560_def_mac); i++)
		RAL_WRITE(sc, rt2560_def_mac[i].reg, rt2560_def_mac[i].val);

	rt2560_set_macaddr(sc, vap ? vap->iv_myaddr : ic->ic_macaddr);

	/* set basic rate set (will be updated later) */
	RAL_WRITE(sc, RT2560_ARSP_PLCP_1, 0x153);

	rt2560_update_slot(ic);
	rt2560_update_plcp(sc);
	rt2560_update_led(sc, 0, 0);

	RAL_WRITE(sc, RT2560_CSR1, RT2560_RESET_ASIC);
	RAL_WRITE(sc, RT2560_CSR1, RT2560_HOST_READY);

	if (rt2560_bbp_init(sc) != 0) {
		rt2560_stop_locked(sc);
		return;
	}

	rt2560_set_txantenna(sc, sc->tx_ant);
	rt2560_set_rxantenna(sc, sc->rx_ant);

	/* set default BSS channel */
	rt2560_set_chan(sc, ic->ic_curchan);

	/* kick Rx */
	tmp = RT2560_DROP_PHY_ERROR | RT2560_DROP_CRC_ERROR;
	if (ic->ic_opmode != IEEE80211_M_MONITOR) {
		tmp |= RT2560_DROP_CTL | RT2560_DROP_VERSION_ERROR;
		if (ic->ic_opmode != IEEE80211_M_HOSTAP &&
		    ic->ic_opmode != IEEE80211_M_MBSS)
			tmp |= RT2560_DROP_TODS;
		if (ic->ic_promisc == 0)
			tmp |= RT2560_DROP_NOT_TO_ME;
	}
	RAL_WRITE(sc, RT2560_RXCSR0, tmp);

	/* clear old FCS and Rx FIFO errors */
	RAL_READ(sc, RT2560_CNT0);
	RAL_READ(sc, RT2560_CNT4);

	/* clear any pending interrupts */
	RAL_WRITE(sc, RT2560_CSR7, 0xffffffff);

	/* enable interrupts */
	RAL_WRITE(sc, RT2560_CSR8, RT2560_INTR_MASK);

	sc->sc_flags |= RT2560_F_RUNNING;

	callout_reset(&sc->watchdog_ch, hz, rt2560_watchdog, sc);
}