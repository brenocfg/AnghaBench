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
typedef  int uint16_t ;
struct vte_hw_stats {int rx_frames; int rx_bcast_frames; int rx_mcast_frames; int rx_runts; int rx_crcerrs; int rx_long_frames; int rx_fifo_full; int rx_desc_unavail; int tx_frames; int tx_underruns; int tx_late_colls; int tx_pause_frames; int rx_pause_frames; } ;
struct vte_softc {struct vte_hw_stats vte_stats; } ;

/* Variables and functions */
 int CSR_READ_2 (struct vte_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VTE_CNT_MECNT0 ; 
 int /*<<< orphan*/  VTE_CNT_MECNT1 ; 
 int /*<<< orphan*/  VTE_CNT_MECNT2 ; 
 int /*<<< orphan*/  VTE_CNT_MECNT3 ; 
 int /*<<< orphan*/  VTE_CNT_MECNT4 ; 
 int /*<<< orphan*/  VTE_CNT_PAUSE ; 
 int /*<<< orphan*/  VTE_CNT_RX_DONE ; 
 int /*<<< orphan*/  VTE_CNT_TX_DONE ; 
 int /*<<< orphan*/  VTE_LOCK_ASSERT (struct vte_softc*) ; 
 int /*<<< orphan*/  VTE_MECISR ; 

__attribute__((used)) static void
vte_stats_update(struct vte_softc *sc)
{
	struct vte_hw_stats *stat;
	uint16_t value;

	VTE_LOCK_ASSERT(sc);

	stat = &sc->vte_stats;

	CSR_READ_2(sc, VTE_MECISR);
	/* RX stats. */
	stat->rx_frames += CSR_READ_2(sc, VTE_CNT_RX_DONE);
	value = CSR_READ_2(sc, VTE_CNT_MECNT0);
	stat->rx_bcast_frames += (value >> 8);
	stat->rx_mcast_frames += (value & 0xFF);
	value = CSR_READ_2(sc, VTE_CNT_MECNT1);
	stat->rx_runts += (value >> 8);
	stat->rx_crcerrs += (value & 0xFF);
	value = CSR_READ_2(sc, VTE_CNT_MECNT2);
	stat->rx_long_frames += (value & 0xFF);
	value = CSR_READ_2(sc, VTE_CNT_MECNT3);
	stat->rx_fifo_full += (value >> 8);
	stat->rx_desc_unavail += (value & 0xFF);

	/* TX stats. */
	stat->tx_frames += CSR_READ_2(sc, VTE_CNT_TX_DONE);
	value = CSR_READ_2(sc, VTE_CNT_MECNT4);
	stat->tx_underruns += (value >> 8);
	stat->tx_late_colls += (value & 0xFF);

	value = CSR_READ_2(sc, VTE_CNT_PAUSE);
	stat->tx_pause_frames += (value >> 8);
	stat->rx_pause_frames += (value & 0xFF);
}