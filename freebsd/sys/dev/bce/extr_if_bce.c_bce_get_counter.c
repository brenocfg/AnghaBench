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
typedef  scalar_t__ uint64_t ;
struct ifnet {int dummy; } ;
struct bce_softc {scalar_t__ stat_Dot3StatsCarrierSenseErrors; scalar_t__ watchdog_timeouts; scalar_t__ stat_Dot3StatsLateCollisions; scalar_t__ stat_emac_tx_stat_dot3statsinternalmactransmiterrors; scalar_t__ stat_Dot3StatsExcessiveCollisions; scalar_t__ com_no_buffers; scalar_t__ l2fhdr_error_count; scalar_t__ stat_IfInFTQDiscards; scalar_t__ stat_IfInRuleCheckerDiscards; scalar_t__ stat_Dot3StatsFCSErrors; scalar_t__ stat_Dot3StatsAlignmentErrors; scalar_t__ stat_IfInMBUFDiscards; scalar_t__ stat_EtherStatsOversizePkts; scalar_t__ stat_EtherStatsUndersizePkts; scalar_t__ stat_EtherStatsCollisions; } ;
typedef  int ift_counter ;

/* Variables and functions */
 int /*<<< orphan*/  BCE_CHIP_ID (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_CHIP_ID_5708_A0 ; 
 int /*<<< orphan*/  BCE_CHIP_NUM (struct bce_softc*) ; 
 int /*<<< orphan*/  BCE_CHIP_NUM_5706 ; 
#define  IFCOUNTER_COLLISIONS 130 
#define  IFCOUNTER_IERRORS 129 
#define  IFCOUNTER_OERRORS 128 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 
 struct bce_softc* if_getsoftc (struct ifnet*) ; 

__attribute__((used)) static uint64_t
bce_get_counter(struct ifnet *ifp, ift_counter cnt)
{
	struct bce_softc *sc;
	uint64_t rv;

	sc = if_getsoftc(ifp);

	switch (cnt) {
	case IFCOUNTER_COLLISIONS:
		return (sc->stat_EtherStatsCollisions);
	case IFCOUNTER_IERRORS:
		return (sc->stat_EtherStatsUndersizePkts +
		    sc->stat_EtherStatsOversizePkts +
		    sc->stat_IfInMBUFDiscards +
		    sc->stat_Dot3StatsAlignmentErrors +
		    sc->stat_Dot3StatsFCSErrors +
		    sc->stat_IfInRuleCheckerDiscards +
		    sc->stat_IfInFTQDiscards +
		    sc->l2fhdr_error_count +
		    sc->com_no_buffers);
	case IFCOUNTER_OERRORS:
		rv = sc->stat_Dot3StatsExcessiveCollisions +
		    sc->stat_emac_tx_stat_dot3statsinternalmactransmiterrors +
		    sc->stat_Dot3StatsLateCollisions +
		    sc->watchdog_timeouts;
		/*
		 * Certain controllers don't report
		 * carrier sense errors correctly.
		 * See errata E11_5708CA0_1165.
		 */
		if (!(BCE_CHIP_NUM(sc) == BCE_CHIP_NUM_5706) &&
		    !(BCE_CHIP_ID(sc) == BCE_CHIP_ID_5708_A0))
			rv += sc->stat_Dot3StatsCarrierSenseErrors;
		return (rv);
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}