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
typedef  int uint16_t ;
struct msk_softc {int dummy; } ;
struct msk_hw_stats {int /*<<< orphan*/  tx_underflows; int /*<<< orphan*/  tx_single_colls; int /*<<< orphan*/  tx_multi_colls; int /*<<< orphan*/  tx_excess_colls; int /*<<< orphan*/  tx_late_colls; int /*<<< orphan*/  tx_colls; int /*<<< orphan*/  tx_pkts_1519_max; int /*<<< orphan*/  tx_pkts_1024_1518; int /*<<< orphan*/  tx_pkts_512_1023; int /*<<< orphan*/  tx_pkts_256_511; int /*<<< orphan*/  tx_pkts_128_255; int /*<<< orphan*/  tx_pkts_65_127; int /*<<< orphan*/  tx_pkts_64; int /*<<< orphan*/  tx_octets; int /*<<< orphan*/  tx_mcast_frames; int /*<<< orphan*/  tx_pause_frames; int /*<<< orphan*/  tx_bcast_frames; int /*<<< orphan*/  tx_ucast_frames; int /*<<< orphan*/  rx_fifo_oflows; int /*<<< orphan*/  rx_pkts_jabbers; int /*<<< orphan*/  rx_pkts_too_long; int /*<<< orphan*/  rx_pkts_1519_max; int /*<<< orphan*/  rx_pkts_1024_1518; int /*<<< orphan*/  rx_pkts_512_1023; int /*<<< orphan*/  rx_pkts_256_511; int /*<<< orphan*/  rx_pkts_128_255; int /*<<< orphan*/  rx_pkts_65_127; int /*<<< orphan*/  rx_pkts_64; int /*<<< orphan*/  rx_runt_errs; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_bad_octets; int /*<<< orphan*/  rx_good_octets; int /*<<< orphan*/  rx_crc_errs; int /*<<< orphan*/  rx_mcast_frames; int /*<<< orphan*/  rx_pause_frames; int /*<<< orphan*/  rx_bcast_frames; int /*<<< orphan*/  rx_ucast_frames; } ;
struct msk_if_softc {int /*<<< orphan*/  msk_port; struct msk_hw_stats msk_stats; struct msk_softc* msk_softc; struct ifnet* msk_ifp; } ;
struct ifnet {int if_drv_flags; } ;

/* Variables and functions */
 int GMAC_READ_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GMAC_WRITE_2 (struct msk_softc*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int GM_PAR_MIB_CLR ; 
 int /*<<< orphan*/  GM_PHY_ADDR ; 
 int /*<<< orphan*/  GM_RXE_FIFO_OV ; 
 int /*<<< orphan*/  GM_RXE_FRAG ; 
 int /*<<< orphan*/  GM_RXF_1023B ; 
 int /*<<< orphan*/  GM_RXF_127B ; 
 int /*<<< orphan*/  GM_RXF_1518B ; 
 int /*<<< orphan*/  GM_RXF_255B ; 
 int /*<<< orphan*/  GM_RXF_511B ; 
 int /*<<< orphan*/  GM_RXF_64B ; 
 int /*<<< orphan*/  GM_RXF_BC_OK ; 
 int /*<<< orphan*/  GM_RXF_FCS_ERR ; 
 int /*<<< orphan*/  GM_RXF_JAB_PKT ; 
 int /*<<< orphan*/  GM_RXF_LNG_ERR ; 
 int /*<<< orphan*/  GM_RXF_MAX_SZ ; 
 int /*<<< orphan*/  GM_RXF_MC_OK ; 
 int /*<<< orphan*/  GM_RXF_MPAUSE ; 
 int /*<<< orphan*/  GM_RXF_SHT ; 
 int /*<<< orphan*/  GM_RXF_SPARE1 ; 
 int /*<<< orphan*/  GM_RXF_SPARE2 ; 
 int /*<<< orphan*/  GM_RXF_SPARE3 ; 
 int /*<<< orphan*/  GM_RXF_UC_OK ; 
 int /*<<< orphan*/  GM_RXO_ERR_LO ; 
 int /*<<< orphan*/  GM_RXO_OK_LO ; 
 int /*<<< orphan*/  GM_TXE_FIFO_UR ; 
 int /*<<< orphan*/  GM_TXF_1023B ; 
 int /*<<< orphan*/  GM_TXF_127B ; 
 int /*<<< orphan*/  GM_TXF_1518B ; 
 int /*<<< orphan*/  GM_TXF_255B ; 
 int /*<<< orphan*/  GM_TXF_511B ; 
 int /*<<< orphan*/  GM_TXF_64B ; 
 int /*<<< orphan*/  GM_TXF_ABO_COL ; 
 int /*<<< orphan*/  GM_TXF_BC_OK ; 
 int /*<<< orphan*/  GM_TXF_COL ; 
 int /*<<< orphan*/  GM_TXF_LAT_COL ; 
 int /*<<< orphan*/  GM_TXF_MAX_SZ ; 
 int /*<<< orphan*/  GM_TXF_MC_OK ; 
 int /*<<< orphan*/  GM_TXF_MPAUSE ; 
 int /*<<< orphan*/  GM_TXF_MUL_COL ; 
 int /*<<< orphan*/  GM_TXF_SNG_COL ; 
 int /*<<< orphan*/  GM_TXF_SPARE1 ; 
 int /*<<< orphan*/  GM_TXF_UC_OK ; 
 int /*<<< orphan*/  GM_TXO_OK_LO ; 
 int IFF_DRV_RUNNING ; 
 int /*<<< orphan*/  MSK_IF_LOCK_ASSERT (struct msk_if_softc*) ; 
 scalar_t__ MSK_READ_MIB32 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ MSK_READ_MIB64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
msk_stats_update(struct msk_if_softc *sc_if)
{
	struct msk_softc *sc;
	struct ifnet *ifp;
	struct msk_hw_stats *stats;
	uint16_t gmac;
	uint32_t reg;

	MSK_IF_LOCK_ASSERT(sc_if);

	ifp = sc_if->msk_ifp;
	if ((ifp->if_drv_flags & IFF_DRV_RUNNING) == 0)
		return;
	sc = sc_if->msk_softc;
	stats = &sc_if->msk_stats;
	/* Set MIB Clear Counter Mode. */
	gmac = GMAC_READ_2(sc, sc_if->msk_port, GM_PHY_ADDR);
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_PHY_ADDR, gmac | GM_PAR_MIB_CLR);

	/* Rx stats. */
	stats->rx_ucast_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_UC_OK);
	stats->rx_bcast_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_BC_OK);
	stats->rx_pause_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_MPAUSE);
	stats->rx_mcast_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_MC_OK);
	stats->rx_crc_errs +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_FCS_ERR);
	reg = MSK_READ_MIB32(sc_if->msk_port, GM_RXF_SPARE1);
	stats->rx_good_octets +=
	    MSK_READ_MIB64(sc_if->msk_port, GM_RXO_OK_LO);
	stats->rx_bad_octets +=
	    MSK_READ_MIB64(sc_if->msk_port, GM_RXO_ERR_LO);
	stats->rx_runts +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_SHT);
	stats->rx_runt_errs +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXE_FRAG);
	stats->rx_pkts_64 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_64B);
	stats->rx_pkts_65_127 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_127B);
	stats->rx_pkts_128_255 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_255B);
	stats->rx_pkts_256_511 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_511B);
	stats->rx_pkts_512_1023 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_1023B);
	stats->rx_pkts_1024_1518 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_1518B);
	stats->rx_pkts_1519_max +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_MAX_SZ);
	stats->rx_pkts_too_long +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_LNG_ERR);
	stats->rx_pkts_jabbers +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXF_JAB_PKT);
	reg = MSK_READ_MIB32(sc_if->msk_port, GM_RXF_SPARE2);
	stats->rx_fifo_oflows +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_RXE_FIFO_OV);
	reg = MSK_READ_MIB32(sc_if->msk_port, GM_RXF_SPARE3);

	/* Tx stats. */
	stats->tx_ucast_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_UC_OK);
	stats->tx_bcast_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_BC_OK);
	stats->tx_pause_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_MPAUSE);
	stats->tx_mcast_frames +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_MC_OK);
	stats->tx_octets +=
	    MSK_READ_MIB64(sc_if->msk_port, GM_TXO_OK_LO);
	stats->tx_pkts_64 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_64B);
	stats->tx_pkts_65_127 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_127B);
	stats->tx_pkts_128_255 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_255B);
	stats->tx_pkts_256_511 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_511B);
	stats->tx_pkts_512_1023 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_1023B);
	stats->tx_pkts_1024_1518 +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_1518B);
	stats->tx_pkts_1519_max +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_MAX_SZ);
	reg = MSK_READ_MIB32(sc_if->msk_port, GM_TXF_SPARE1);
	stats->tx_colls +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_COL);
	stats->tx_late_colls +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_LAT_COL);
	stats->tx_excess_colls +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_ABO_COL);
	stats->tx_multi_colls +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_MUL_COL);
	stats->tx_single_colls +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXF_SNG_COL);
	stats->tx_underflows +=
	    MSK_READ_MIB32(sc_if->msk_port, GM_TXE_FIFO_UR);
	/* Clear MIB Clear Counter Mode. */
	gmac &= ~GM_PAR_MIB_CLR;
	GMAC_WRITE_2(sc, sc_if->msk_port, GM_PHY_ADDR, gmac);
}