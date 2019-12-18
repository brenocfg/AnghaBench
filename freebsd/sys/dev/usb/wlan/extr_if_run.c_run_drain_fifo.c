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
typedef  size_t uint8_t ;
typedef  int uint32_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {int /*<<< orphan*/  ic_oerrors; } ;
struct run_softc {scalar_t__** wcid_stats; int fifo_cnt; TYPE_1__ sc_ic; } ;
typedef  scalar_t__ int8_t ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int RT2860_TXQ_ACKREQ ; 
 int RT2860_TXQ_MCS_SHIFT ; 
 int RT2860_TXQ_OK ; 
 int RT2860_TXQ_PID_SHIFT ; 
 int RT2860_TXQ_VLD ; 
 int RT2860_TXQ_WCID_SHIFT ; 
 int /*<<< orphan*/  RT2860_TX_STAT_FIFO ; 
 size_t RT2870_WCID_MAX ; 
 int /*<<< orphan*/  RUN_DEBUG_XMIT ; 
 int /*<<< orphan*/  RUN_DPRINTF (struct run_softc*,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  RUN_LOCK_ASSERT (struct run_softc*,int /*<<< orphan*/ ) ; 
 size_t RUN_RETRY ; 
 size_t RUN_SUCCESS ; 
 size_t RUN_TXCNT ; 
 int /*<<< orphan*/  counter_u64_add (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  run_read (struct run_softc*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
run_drain_fifo(void *arg)
{
	struct run_softc *sc = arg;
	uint32_t stat;
	uint16_t (*wstat)[3];
	uint8_t wcid, mcs, pid;
	int8_t retry;

	RUN_LOCK_ASSERT(sc, MA_OWNED);

	for (;;) {
		/* drain Tx status FIFO (maxsize = 16) */
		run_read(sc, RT2860_TX_STAT_FIFO, &stat);
		RUN_DPRINTF(sc, RUN_DEBUG_XMIT, "tx stat 0x%08x\n", stat);
		if (!(stat & RT2860_TXQ_VLD))
			break;

		wcid = (stat >> RT2860_TXQ_WCID_SHIFT) & 0xff;

		/* if no ACK was requested, no feedback is available */
		if (!(stat & RT2860_TXQ_ACKREQ) || wcid > RT2870_WCID_MAX ||
		    wcid == 0)
			continue;

		/*
		 * Even though each stat is Tx-complete-status like format,
		 * the device can poll stats. Because there is no guarantee
		 * that the referring node is still around when read the stats.
		 * So that, if we use ieee80211_ratectl_tx_update(), we will
		 * have hard time not to refer already freed node.
		 *
		 * To eliminate such page faults, we poll stats in softc.
		 * Then, update the rates later with ieee80211_ratectl_tx_update().
		 */
		wstat = &(sc->wcid_stats[wcid]);
		(*wstat)[RUN_TXCNT]++;
		if (stat & RT2860_TXQ_OK)
			(*wstat)[RUN_SUCCESS]++;
		else
			counter_u64_add(sc->sc_ic.ic_oerrors, 1);
		/*
		 * Check if there were retries, ie if the Tx success rate is
		 * different from the requested rate. Note that it works only
		 * because we do not allow rate fallback from OFDM to CCK.
		 */
		mcs = (stat >> RT2860_TXQ_MCS_SHIFT) & 0x7f;
		pid = (stat >> RT2860_TXQ_PID_SHIFT) & 0xf;
		if ((retry = pid -1 - mcs) > 0) {
			(*wstat)[RUN_TXCNT] += retry;
			(*wstat)[RUN_RETRY] += retry;
		}
	}
	RUN_DPRINTF(sc, RUN_DEBUG_XMIT, "count=%d\n", sc->fifo_cnt);

	sc->fifo_cnt = 0;
}