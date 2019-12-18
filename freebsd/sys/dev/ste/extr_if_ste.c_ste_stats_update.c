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
struct ste_hw_stats {int rx_bytes; int rx_bcast_frames; int rx_mcast_frames; int rx_lost_frames; int tx_bytes; int tx_bcast_frames; int tx_mcast_frames; int tx_carrsense_errs; int tx_single_colls; int tx_multi_colls; int tx_late_colls; int tx_frames_defered; int tx_excess_defers; int tx_abort; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  rx_frames; } ;
struct ste_softc {struct ste_hw_stats ste_stats; struct ifnet* ste_ifp; } ;
struct ifnet {int dummy; } ;

/* Variables and functions */
 int CSR_READ_1 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 scalar_t__ CSR_READ_2 (struct ste_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IFCOUNTER_COLLISIONS ; 
 int /*<<< orphan*/  STE_LOCK_ASSERT (struct ste_softc*) ; 
 int /*<<< orphan*/  STE_STAT_CARRIER_ERR ; 
 int /*<<< orphan*/  STE_STAT_LATE_COLLS ; 
 int /*<<< orphan*/  STE_STAT_MULTI_COLLS ; 
 int /*<<< orphan*/  STE_STAT_RX_BCAST ; 
 int /*<<< orphan*/  STE_STAT_RX_FRAMES ; 
 int /*<<< orphan*/  STE_STAT_RX_LOST ; 
 int /*<<< orphan*/  STE_STAT_RX_MCAST ; 
 int /*<<< orphan*/  STE_STAT_RX_OCTETS_HI ; 
 int /*<<< orphan*/  STE_STAT_RX_OCTETS_LO ; 
 int /*<<< orphan*/  STE_STAT_SINGLE_COLLS ; 
 int /*<<< orphan*/  STE_STAT_TX_ABORT ; 
 int /*<<< orphan*/  STE_STAT_TX_BCAST ; 
 int /*<<< orphan*/  STE_STAT_TX_DEFER ; 
 int /*<<< orphan*/  STE_STAT_TX_EXDEFER ; 
 int /*<<< orphan*/  STE_STAT_TX_FRAMES ; 
 int /*<<< orphan*/  STE_STAT_TX_MCAST ; 
 int /*<<< orphan*/  STE_STAT_TX_OCTETS_HI ; 
 int /*<<< orphan*/  STE_STAT_TX_OCTETS_LO ; 
 int /*<<< orphan*/  if_inc_counter (struct ifnet*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ste_stats_update(struct ste_softc *sc)
{
	struct ifnet *ifp;
	struct ste_hw_stats *stats;
	uint32_t val;

	STE_LOCK_ASSERT(sc);

	ifp = sc->ste_ifp;
	stats = &sc->ste_stats;
	/* Rx stats. */
	val = (uint32_t)CSR_READ_2(sc, STE_STAT_RX_OCTETS_LO) |
	    ((uint32_t)CSR_READ_2(sc, STE_STAT_RX_OCTETS_HI)) << 16;
	val &= 0x000FFFFF;
	stats->rx_bytes += val;
	stats->rx_frames += CSR_READ_2(sc, STE_STAT_RX_FRAMES);
	stats->rx_bcast_frames += CSR_READ_1(sc, STE_STAT_RX_BCAST);
	stats->rx_mcast_frames += CSR_READ_1(sc, STE_STAT_RX_MCAST);
	stats->rx_lost_frames += CSR_READ_1(sc, STE_STAT_RX_LOST);
	/* Tx stats. */
	val = (uint32_t)CSR_READ_2(sc, STE_STAT_TX_OCTETS_LO) |
	    ((uint32_t)CSR_READ_2(sc, STE_STAT_TX_OCTETS_HI)) << 16;
	val &= 0x000FFFFF;
	stats->tx_bytes += val;
	stats->tx_frames += CSR_READ_2(sc, STE_STAT_TX_FRAMES);
	stats->tx_bcast_frames += CSR_READ_1(sc, STE_STAT_TX_BCAST);
	stats->tx_mcast_frames += CSR_READ_1(sc, STE_STAT_TX_MCAST);
	stats->tx_carrsense_errs += CSR_READ_1(sc, STE_STAT_CARRIER_ERR);
	val = CSR_READ_1(sc, STE_STAT_SINGLE_COLLS);
	stats->tx_single_colls += val;
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, val);
	val = CSR_READ_1(sc, STE_STAT_MULTI_COLLS);
	stats->tx_multi_colls += val;
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, val);
	val += CSR_READ_1(sc, STE_STAT_LATE_COLLS);
	stats->tx_late_colls += val;
	if_inc_counter(ifp, IFCOUNTER_COLLISIONS, val);
	stats->tx_frames_defered += CSR_READ_1(sc, STE_STAT_TX_DEFER);
	stats->tx_excess_defers += CSR_READ_1(sc, STE_STAT_TX_EXDEFER);
	stats->tx_abort += CSR_READ_1(sc, STE_STAT_TX_ABORT);
}