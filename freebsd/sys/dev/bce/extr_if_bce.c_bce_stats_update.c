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
typedef  int u64 ;
struct statistics_block {int /*<<< orphan*/  stat_CatchupInRuleCheckerP4Hit; int /*<<< orphan*/  stat_CatchupInMBUFDiscards; int /*<<< orphan*/  stat_CatchupInFTQDiscards; int /*<<< orphan*/  stat_CatchupInRuleCheckerDiscards; int /*<<< orphan*/  stat_IfInRuleCheckerP4Hit; int /*<<< orphan*/  stat_IfInMBUFDiscards; int /*<<< orphan*/  stat_IfInFTQDiscards; int /*<<< orphan*/  stat_IfInRuleCheckerDiscards; int /*<<< orphan*/  stat_IfInFramesL2FilterDiscards; int /*<<< orphan*/  stat_XoffStateEntered; int /*<<< orphan*/  stat_MacControlFramesReceived; int /*<<< orphan*/  stat_FlowControlDone; int /*<<< orphan*/  stat_OutXoffSent; int /*<<< orphan*/  stat_OutXonSent; int /*<<< orphan*/  stat_XoffPauseFramesReceived; int /*<<< orphan*/  stat_XonPauseFramesReceived; int /*<<< orphan*/  stat_EtherStatsPktsTx1523Octetsto9022Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx1024Octetsto1522Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx512Octetsto1023Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx256Octetsto511Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx128Octetsto255Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx65Octetsto127Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx64Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx1523Octetsto9022Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx1024Octetsto1522Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx512Octetsto1023Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx256Octetsto511Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx128Octetsto255Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx65Octetsto127Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx64Octets; int /*<<< orphan*/  stat_EtherStatsOversizePkts; int /*<<< orphan*/  stat_EtherStatsUndersizePkts; int /*<<< orphan*/  stat_EtherStatsJabbers; int /*<<< orphan*/  stat_EtherStatsFragments; int /*<<< orphan*/  stat_EtherStatsCollisions; int /*<<< orphan*/  stat_Dot3StatsLateCollisions; int /*<<< orphan*/  stat_Dot3StatsExcessiveCollisions; int /*<<< orphan*/  stat_Dot3StatsDeferredTransmissions; int /*<<< orphan*/  stat_Dot3StatsMultipleCollisionFrames; int /*<<< orphan*/  stat_Dot3StatsSingleCollisionFrames; int /*<<< orphan*/  stat_Dot3StatsAlignmentErrors; int /*<<< orphan*/  stat_Dot3StatsFCSErrors; int /*<<< orphan*/  stat_Dot3StatsCarrierSenseErrors; int /*<<< orphan*/  stat_emac_tx_stat_dot3statsinternalmactransmiterrors; scalar_t__ stat_IfHCOutBroadcastPkts_lo; scalar_t__ stat_IfHCOutBroadcastPkts_hi; scalar_t__ stat_IfHCOutMulticastPkts_lo; scalar_t__ stat_IfHCOutMulticastPkts_hi; scalar_t__ stat_IfHCOutUcastPkts_lo; scalar_t__ stat_IfHCOutUcastPkts_hi; scalar_t__ stat_IfHCInBroadcastPkts_lo; scalar_t__ stat_IfHCInBroadcastPkts_hi; scalar_t__ stat_IfHCInMulticastPkts_lo; scalar_t__ stat_IfHCInMulticastPkts_hi; scalar_t__ stat_IfHCInUcastPkts_lo; scalar_t__ stat_IfHCInUcastPkts_hi; scalar_t__ stat_IfHCOutBadOctets_lo; scalar_t__ stat_IfHCOutBadOctets_hi; scalar_t__ stat_IfHCOutOctets_lo; scalar_t__ stat_IfHCOutOctets_hi; scalar_t__ stat_IfHCInBadOctets_lo; scalar_t__ stat_IfHCInBadOctets_hi; scalar_t__ stat_IfHCInOctets_lo; scalar_t__ stat_IfHCInOctets_hi; } ;
struct bce_softc {int stat_IfHCInOctets; int stat_IfHCInBadOctets; int stat_IfHCOutOctets; int stat_IfHCOutBadOctets; int stat_IfHCInUcastPkts; int stat_IfHCInMulticastPkts; int stat_IfHCInBroadcastPkts; int stat_IfHCOutUcastPkts; int stat_IfHCOutMulticastPkts; int stat_IfHCOutBroadcastPkts; int /*<<< orphan*/  com_no_buffers; int /*<<< orphan*/  stat_CatchupInRuleCheckerP4Hit; int /*<<< orphan*/  stat_CatchupInMBUFDiscards; int /*<<< orphan*/  stat_CatchupInFTQDiscards; int /*<<< orphan*/  stat_CatchupInRuleCheckerDiscards; int /*<<< orphan*/  stat_IfInRuleCheckerP4Hit; int /*<<< orphan*/  stat_IfInMBUFDiscards; int /*<<< orphan*/  stat_IfInFTQDiscards; int /*<<< orphan*/  stat_IfInRuleCheckerDiscards; int /*<<< orphan*/  stat_IfInFramesL2FilterDiscards; int /*<<< orphan*/  stat_XoffStateEntered; int /*<<< orphan*/  stat_MacControlFramesReceived; int /*<<< orphan*/  stat_FlowControlDone; int /*<<< orphan*/  stat_OutXoffSent; int /*<<< orphan*/  stat_OutXonSent; int /*<<< orphan*/  stat_XoffPauseFramesReceived; int /*<<< orphan*/  stat_XonPauseFramesReceived; int /*<<< orphan*/  stat_EtherStatsPktsTx1523Octetsto9022Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx1024Octetsto1522Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx512Octetsto1023Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx256Octetsto511Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx128Octetsto255Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx65Octetsto127Octets; int /*<<< orphan*/  stat_EtherStatsPktsTx64Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx1523Octetsto9022Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx1024Octetsto1522Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx512Octetsto1023Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx256Octetsto511Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx128Octetsto255Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx65Octetsto127Octets; int /*<<< orphan*/  stat_EtherStatsPktsRx64Octets; int /*<<< orphan*/  stat_EtherStatsOversizePkts; int /*<<< orphan*/  stat_EtherStatsUndersizePkts; int /*<<< orphan*/  stat_EtherStatsJabbers; int /*<<< orphan*/  stat_EtherStatsFragments; int /*<<< orphan*/  stat_EtherStatsCollisions; int /*<<< orphan*/  stat_Dot3StatsLateCollisions; int /*<<< orphan*/  stat_Dot3StatsExcessiveCollisions; int /*<<< orphan*/  stat_Dot3StatsDeferredTransmissions; int /*<<< orphan*/  stat_Dot3StatsMultipleCollisionFrames; int /*<<< orphan*/  stat_Dot3StatsSingleCollisionFrames; int /*<<< orphan*/  stat_Dot3StatsAlignmentErrors; int /*<<< orphan*/  stat_Dot3StatsFCSErrors; int /*<<< orphan*/  stat_Dot3StatsCarrierSenseErrors; int /*<<< orphan*/  stat_emac_tx_stat_dot3statsinternalmactransmiterrors; scalar_t__ stats_block; int /*<<< orphan*/  stats_map; int /*<<< orphan*/  stats_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_EXTREME_MISC ; 
 int /*<<< orphan*/  BUS_DMASYNC_POSTREAD ; 
 int /*<<< orphan*/  DBENTER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DBEXIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_RD_IND (struct bce_softc*,int) ; 
 int /*<<< orphan*/  bus_dmamap_sync (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bce_stats_update(struct bce_softc *sc)
{
	struct statistics_block *stats;

	DBENTER(BCE_EXTREME_MISC);

	bus_dmamap_sync(sc->stats_tag, sc->stats_map, BUS_DMASYNC_POSTREAD);

	stats = (struct statistics_block *) sc->stats_block;

	/*
	 * Update the sysctl statistics from the
	 * hardware statistics.
	 */
	sc->stat_IfHCInOctets =
	    ((u64) stats->stat_IfHCInOctets_hi << 32) +
	     (u64) stats->stat_IfHCInOctets_lo;

	sc->stat_IfHCInBadOctets =
	    ((u64) stats->stat_IfHCInBadOctets_hi << 32) +
	     (u64) stats->stat_IfHCInBadOctets_lo;

	sc->stat_IfHCOutOctets =
	    ((u64) stats->stat_IfHCOutOctets_hi << 32) +
	     (u64) stats->stat_IfHCOutOctets_lo;

	sc->stat_IfHCOutBadOctets =
	    ((u64) stats->stat_IfHCOutBadOctets_hi << 32) +
	     (u64) stats->stat_IfHCOutBadOctets_lo;

	sc->stat_IfHCInUcastPkts =
	    ((u64) stats->stat_IfHCInUcastPkts_hi << 32) +
	     (u64) stats->stat_IfHCInUcastPkts_lo;

	sc->stat_IfHCInMulticastPkts =
	    ((u64) stats->stat_IfHCInMulticastPkts_hi << 32) +
	     (u64) stats->stat_IfHCInMulticastPkts_lo;

	sc->stat_IfHCInBroadcastPkts =
	    ((u64) stats->stat_IfHCInBroadcastPkts_hi << 32) +
	     (u64) stats->stat_IfHCInBroadcastPkts_lo;

	sc->stat_IfHCOutUcastPkts =
	    ((u64) stats->stat_IfHCOutUcastPkts_hi << 32) +
	     (u64) stats->stat_IfHCOutUcastPkts_lo;

	sc->stat_IfHCOutMulticastPkts =
	    ((u64) stats->stat_IfHCOutMulticastPkts_hi << 32) +
	     (u64) stats->stat_IfHCOutMulticastPkts_lo;

	sc->stat_IfHCOutBroadcastPkts =
	    ((u64) stats->stat_IfHCOutBroadcastPkts_hi << 32) +
	     (u64) stats->stat_IfHCOutBroadcastPkts_lo;

	/* ToDo: Preserve counters beyond 32 bits? */
	/* ToDo: Read the statistics from auto-clear regs? */

	sc->stat_emac_tx_stat_dot3statsinternalmactransmiterrors =
	    stats->stat_emac_tx_stat_dot3statsinternalmactransmiterrors;

	sc->stat_Dot3StatsCarrierSenseErrors =
	    stats->stat_Dot3StatsCarrierSenseErrors;

	sc->stat_Dot3StatsFCSErrors =
	    stats->stat_Dot3StatsFCSErrors;

	sc->stat_Dot3StatsAlignmentErrors =
	    stats->stat_Dot3StatsAlignmentErrors;

	sc->stat_Dot3StatsSingleCollisionFrames =
	    stats->stat_Dot3StatsSingleCollisionFrames;

	sc->stat_Dot3StatsMultipleCollisionFrames =
	    stats->stat_Dot3StatsMultipleCollisionFrames;

	sc->stat_Dot3StatsDeferredTransmissions =
	    stats->stat_Dot3StatsDeferredTransmissions;

	sc->stat_Dot3StatsExcessiveCollisions =
	    stats->stat_Dot3StatsExcessiveCollisions;

	sc->stat_Dot3StatsLateCollisions =
	    stats->stat_Dot3StatsLateCollisions;

	sc->stat_EtherStatsCollisions =
	    stats->stat_EtherStatsCollisions;

	sc->stat_EtherStatsFragments =
	    stats->stat_EtherStatsFragments;

	sc->stat_EtherStatsJabbers =
	    stats->stat_EtherStatsJabbers;

	sc->stat_EtherStatsUndersizePkts =
	    stats->stat_EtherStatsUndersizePkts;

	sc->stat_EtherStatsOversizePkts =
	     stats->stat_EtherStatsOversizePkts;

	sc->stat_EtherStatsPktsRx64Octets =
	    stats->stat_EtherStatsPktsRx64Octets;

	sc->stat_EtherStatsPktsRx65Octetsto127Octets =
	    stats->stat_EtherStatsPktsRx65Octetsto127Octets;

	sc->stat_EtherStatsPktsRx128Octetsto255Octets =
	    stats->stat_EtherStatsPktsRx128Octetsto255Octets;

	sc->stat_EtherStatsPktsRx256Octetsto511Octets =
	    stats->stat_EtherStatsPktsRx256Octetsto511Octets;

	sc->stat_EtherStatsPktsRx512Octetsto1023Octets =
	    stats->stat_EtherStatsPktsRx512Octetsto1023Octets;

	sc->stat_EtherStatsPktsRx1024Octetsto1522Octets =
	    stats->stat_EtherStatsPktsRx1024Octetsto1522Octets;

	sc->stat_EtherStatsPktsRx1523Octetsto9022Octets =
	    stats->stat_EtherStatsPktsRx1523Octetsto9022Octets;

	sc->stat_EtherStatsPktsTx64Octets =
	    stats->stat_EtherStatsPktsTx64Octets;

	sc->stat_EtherStatsPktsTx65Octetsto127Octets =
	    stats->stat_EtherStatsPktsTx65Octetsto127Octets;

	sc->stat_EtherStatsPktsTx128Octetsto255Octets =
	    stats->stat_EtherStatsPktsTx128Octetsto255Octets;

	sc->stat_EtherStatsPktsTx256Octetsto511Octets =
	    stats->stat_EtherStatsPktsTx256Octetsto511Octets;

	sc->stat_EtherStatsPktsTx512Octetsto1023Octets =
	    stats->stat_EtherStatsPktsTx512Octetsto1023Octets;

	sc->stat_EtherStatsPktsTx1024Octetsto1522Octets =
	    stats->stat_EtherStatsPktsTx1024Octetsto1522Octets;

	sc->stat_EtherStatsPktsTx1523Octetsto9022Octets =
	    stats->stat_EtherStatsPktsTx1523Octetsto9022Octets;

	sc->stat_XonPauseFramesReceived =
	    stats->stat_XonPauseFramesReceived;

	sc->stat_XoffPauseFramesReceived =
	    stats->stat_XoffPauseFramesReceived;

	sc->stat_OutXonSent =
	    stats->stat_OutXonSent;

	sc->stat_OutXoffSent =
	    stats->stat_OutXoffSent;

	sc->stat_FlowControlDone =
	    stats->stat_FlowControlDone;

	sc->stat_MacControlFramesReceived =
	    stats->stat_MacControlFramesReceived;

	sc->stat_XoffStateEntered =
	    stats->stat_XoffStateEntered;

	sc->stat_IfInFramesL2FilterDiscards =
	    stats->stat_IfInFramesL2FilterDiscards;

	sc->stat_IfInRuleCheckerDiscards =
	    stats->stat_IfInRuleCheckerDiscards;

	sc->stat_IfInFTQDiscards =
	    stats->stat_IfInFTQDiscards;

	sc->stat_IfInMBUFDiscards =
	    stats->stat_IfInMBUFDiscards;

	sc->stat_IfInRuleCheckerP4Hit =
	    stats->stat_IfInRuleCheckerP4Hit;

	sc->stat_CatchupInRuleCheckerDiscards =
	    stats->stat_CatchupInRuleCheckerDiscards;

	sc->stat_CatchupInFTQDiscards =
	    stats->stat_CatchupInFTQDiscards;

	sc->stat_CatchupInMBUFDiscards =
	    stats->stat_CatchupInMBUFDiscards;

	sc->stat_CatchupInRuleCheckerP4Hit =
	    stats->stat_CatchupInRuleCheckerP4Hit;

	sc->com_no_buffers = REG_RD_IND(sc, 0x120084);

	/* ToDo: Add additional statistics? */

	DBEXIT(BCE_EXTREME_MISC);
}