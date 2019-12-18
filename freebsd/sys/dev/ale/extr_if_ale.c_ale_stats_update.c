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
typedef  scalar_t__ uint32_t ;
struct smb {int tx_multi_colls; int tx_excess_colls; scalar_t__ rx_alignerrs; scalar_t__ rx_rrs_errs; scalar_t__ rx_fifo_oflows; scalar_t__ rx_pkts_truncated; scalar_t__ rx_runts; scalar_t__ rx_lenerrs; scalar_t__ rx_crcerrs; scalar_t__ rx_frames; scalar_t__ tx_pkts_truncated; scalar_t__ tx_underrun; scalar_t__ tx_late_colls; scalar_t__ tx_single_colls; scalar_t__ tx_frames; scalar_t__ tx_mcast_bytes; scalar_t__ tx_bcast_bytes; scalar_t__ tx_lenerrs; scalar_t__ tx_desc_underrun; scalar_t__ tx_pkts_1519_max; scalar_t__ tx_pkts_1024_1518; scalar_t__ tx_pkts_512_1023; scalar_t__ tx_pkts_256_511; scalar_t__ tx_pkts_128_255; scalar_t__ tx_pkts_65_127; scalar_t__ tx_pkts_64; scalar_t__ tx_bytes; scalar_t__ tx_deferred; scalar_t__ tx_control_frames; scalar_t__ tx_excess_defer; scalar_t__ tx_pause_frames; scalar_t__ tx_mcast_frames; scalar_t__ tx_bcast_frames; scalar_t__ rx_pkts_filtered; scalar_t__ rx_mcast_bytes; scalar_t__ rx_bcast_bytes; scalar_t__ rx_pkts_1519_max; scalar_t__ rx_pkts_1024_1518; scalar_t__ rx_pkts_512_1023; scalar_t__ rx_pkts_256_511; scalar_t__ rx_pkts_128_255; scalar_t__ rx_pkts_65_127; scalar_t__ rx_pkts_64; scalar_t__ rx_fragments; scalar_t__ rx_bytes; scalar_t__ rx_control_frames; scalar_t__ rx_pause_frames; scalar_t__ rx_mcast_frames; scalar_t__ rx_bcast_frames; } ;
struct ifnet {int dummy; } ;
struct ale_hw_stats {int tx_multi_colls; int tx_excess_colls; int /*<<< orphan*/  tx_mcast_bytes; int /*<<< orphan*/  tx_bcast_bytes; int /*<<< orphan*/  tx_pkts_truncated; int /*<<< orphan*/  tx_lenerrs; int /*<<< orphan*/  tx_desc_underrun; int /*<<< orphan*/  tx_underrun; int /*<<< orphan*/  tx_late_colls; int /*<<< orphan*/  tx_single_colls; int /*<<< orphan*/  tx_pkts_1519_max; int /*<<< orphan*/  tx_pkts_1024_1518; int /*<<< orphan*/  tx_pkts_512_1023; int /*<<< orphan*/  tx_pkts_256_511; int /*<<< orphan*/  tx_pkts_128_255; int /*<<< orphan*/  tx_pkts_65_127; int /*<<< orphan*/  tx_pkts_64; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  tx_deferred; int /*<<< orphan*/  tx_control_frames; int /*<<< orphan*/  tx_excess_defer; int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  tx_mcast_frames; int /*<<< orphan*/  tx_bcast_frames; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_pkts_filtered; int /*<<< orphan*/  rx_mcast_bytes; int /*<<< orphan*/  rx_bcast_bytes; int /*<<< orphan*/  rx_alignerrs; int /*<<< orphan*/  rx_rrs_errs; int /*<<< orphan*/  rx_fifo_oflows; int /*<<< orphan*/  rx_pkts_truncated; int /*<<< orphan*/  rx_pkts_1519_max; int /*<<< orphan*/  rx_pkts_1024_1518; int /*<<< orphan*/  rx_pkts_512_1023; int /*<<< orphan*/  rx_pkts_256_511; int /*<<< orphan*/  rx_pkts_128_255; int /*<<< orphan*/  rx_pkts_65_127; int /*<<< orphan*/  rx_pkts_64; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  rx_lenerrs; int /*<<< orphan*/  rx_crcerrs; int /*<<< orphan*/  rx_control_frames; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_bcast_frames; int /*<<< orphan*/  rx_frames; } ;
struct ale_softc {struct ale_hw_stats ale_stats; struct ifnet* ale_ifp; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALE_LOCK_ASSERT (struct ale_softc*) ; 
 scalar_t__ ALE_RX_MIB_BASE ; 
 scalar_t__ ALE_TX_MIB_BASE ; 
 scalar_t__ CSR_READ_4 (struct ale_softc*,scalar_t__) ; 
 int HDPX_CFG_RETRY_DEFAULT ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  IFCOUNTER_IERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_IPACKETS ; 
 int /*<<< orphan*/  IFCOUNTER_OERRORS ; 
 int /*<<< orphan*/  IFCOUNTER_OPACKETS ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
ale_stats_update(struct ale_softc *sc)
{
	struct ale_hw_stats *stat;
	struct smb sb, *smb;
	struct ifnet *ifp;
	uint32_t *reg;
	int i;

	ALE_LOCK_ASSERT(sc);

	ifp = sc->ale_ifp;
	stat = &sc->ale_stats;
	smb = &sb;

	/* Read Rx statistics. */
	for (reg = &sb.rx_frames, i = 0; reg <= &sb.rx_pkts_filtered; reg++) {
		*reg = CSR_READ_4(sc, ALE_RX_MIB_BASE + i);
		i += sizeof(uint32_t);
	}
	/* Read Tx statistics. */
	for (reg = &sb.tx_frames, i = 0; reg <= &sb.tx_mcast_bytes; reg++) {
		*reg = CSR_READ_4(sc, ALE_TX_MIB_BASE + i);
		i += sizeof(uint32_t);
	}

	/* Rx stats. */
	stat->rx_frames += smb->rx_frames;
	stat->rx_bcast_frames += smb->rx_bcast_frames;
	stat->rx_mcast_frames += smb->rx_mcast_frames;
	stat->rx_pause_frames += smb->rx_pause_frames;
	stat->rx_control_frames += smb->rx_control_frames;
	stat->rx_crcerrs += smb->rx_crcerrs;
	stat->rx_lenerrs += smb->rx_lenerrs;
	stat->rx_bytes += smb->rx_bytes;
	stat->rx_runts += smb->rx_runts;
	stat->rx_fragments += smb->rx_fragments;
	stat->rx_pkts_64 += smb->rx_pkts_64;
	stat->rx_pkts_65_127 += smb->rx_pkts_65_127;
	stat->rx_pkts_128_255 += smb->rx_pkts_128_255;
	stat->rx_pkts_256_511 += smb->rx_pkts_256_511;
	stat->rx_pkts_512_1023 += smb->rx_pkts_512_1023;
	stat->rx_pkts_1024_1518 += smb->rx_pkts_1024_1518;
	stat->rx_pkts_1519_max += smb->rx_pkts_1519_max;
	stat->rx_pkts_truncated += smb->rx_pkts_truncated;
	stat->rx_fifo_oflows += smb->rx_fifo_oflows;
	stat->rx_rrs_errs += smb->rx_rrs_errs;
	stat->rx_alignerrs += smb->rx_alignerrs;
	stat->rx_bcast_bytes += smb->rx_bcast_bytes;
	stat->rx_mcast_bytes += smb->rx_mcast_bytes;
	stat->rx_pkts_filtered += smb->rx_pkts_filtered;

	/* Tx stats. */
	stat->tx_frames += smb->tx_frames;
	stat->tx_bcast_frames += smb->tx_bcast_frames;
	stat->tx_mcast_frames += smb->tx_mcast_frames;
	stat->tx_pause_frames += smb->tx_pause_frames;
	stat->tx_excess_defer += smb->tx_excess_defer;
	stat->tx_control_frames += smb->tx_control_frames;
	stat->tx_deferred += smb->tx_deferred;
	stat->tx_bytes += smb->tx_bytes;
	stat->tx_pkts_64 += smb->tx_pkts_64;
	stat->tx_pkts_65_127 += smb->tx_pkts_65_127;
	stat->tx_pkts_128_255 += smb->tx_pkts_128_255;
	stat->tx_pkts_256_511 += smb->tx_pkts_256_511;
	stat->tx_pkts_512_1023 += smb->tx_pkts_512_1023;
	stat->tx_pkts_1024_1518 += smb->tx_pkts_1024_1518;
	stat->tx_pkts_1519_max += smb->tx_pkts_1519_max;
	stat->tx_single_colls += smb->tx_single_colls;
	stat->tx_multi_colls += smb->tx_multi_colls;
	stat->tx_late_colls += smb->tx_late_colls;
	stat->tx_excess_colls += smb->tx_excess_colls;
	stat->tx_underrun += smb->tx_underrun;
	stat->tx_desc_underrun += smb->tx_desc_underrun;
	stat->tx_lenerrs += smb->tx_lenerrs;
	stat->tx_pkts_truncated += smb->tx_pkts_truncated;
	stat->tx_bcast_bytes += smb->tx_bcast_bytes;
	stat->tx_mcast_bytes += smb->tx_mcast_bytes;

	/* Update counters in ifnet. */
	if_inc_counter(ifp, IFCOUNTER_OPACKETS, smb->tx_frames);

	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, smb->tx_single_colls +
	    smb->tx_multi_colls * 2 + smb->tx_late_colls +
	    smb->tx_excess_colls * HDPX_CFG_RETRY_DEFAULT);

	if_inc_counter(ifp, IFCOUNTER_OERRORS, smb->tx_late_colls +
	    smb->tx_excess_colls + smb->tx_underrun + smb->tx_pkts_truncated);

	if_inc_counter(ifp, IFCOUNTER_IPACKETS, smb->rx_frames);

	if_inc_counter(ifp, IFCOUNTER_IERRORS,
	    smb->rx_crcerrs + smb->rx_lenerrs +
	    smb->rx_runts + smb->rx_pkts_truncated +
	    smb->rx_fifo_oflows + smb->rx_rrs_errs +
	    smb->rx_alignerrs);
}