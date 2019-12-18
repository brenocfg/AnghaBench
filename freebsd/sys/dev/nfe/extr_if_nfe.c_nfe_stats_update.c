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
struct nfe_hw_stats {int /*<<< orphan*/  tx_broadcast; int /*<<< orphan*/  tx_multicast; int /*<<< orphan*/  tx_unicast; int /*<<< orphan*/  rx_drops; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  rx_octets; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_deferals; int /*<<< orphan*/  rx_broadcast; int /*<<< orphan*/  rx_multicast; int /*<<< orphan*/  rx_unicast; int /*<<< orphan*/  rx_len_errors; int /*<<< orphan*/  rx_fae; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_fifo_overuns; int /*<<< orphan*/  rx_jumbos; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_late_cols; int /*<<< orphan*/  rx_extra_bytes; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  tx_retry_errors; int /*<<< orphan*/  tx_excess_deferals; int /*<<< orphan*/  tx_carrier_losts; int /*<<< orphan*/  tx_fifo_underuns; int /*<<< orphan*/  tx_late_cols; int /*<<< orphan*/  tx_multi_rexmits; int /*<<< orphan*/  tx_one_rexmits; int /*<<< orphan*/  tx_zero_rexmits; int /*<<< orphan*/  tx_octets; } ;
struct nfe_softc {int nfe_flags; struct nfe_hw_stats nfe_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFE_LOCK_ASSERT (struct nfe_softc*) ; 
 int NFE_MIB_V1 ; 
 int NFE_MIB_V2 ; 
 int NFE_MIB_V3 ; 
 scalar_t__ NFE_READ (struct nfe_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NFE_RX_BROADCAST ; 
 int /*<<< orphan*/  NFE_RX_CRC_ERROR ; 
 int /*<<< orphan*/  NFE_RX_DROP ; 
 int /*<<< orphan*/  NFE_RX_EXTRA_BYTES ; 
 int /*<<< orphan*/  NFE_RX_FAE ; 
 int /*<<< orphan*/  NFE_RX_FIFO_OVERUN ; 
 int /*<<< orphan*/  NFE_RX_FRAME_ERROR ; 
 int /*<<< orphan*/  NFE_RX_JUMBO ; 
 int /*<<< orphan*/  NFE_RX_LATE_COL ; 
 int /*<<< orphan*/  NFE_RX_LEN_ERROR ; 
 int /*<<< orphan*/  NFE_RX_MULTICAST ; 
 int /*<<< orphan*/  NFE_RX_OCTET ; 
 int /*<<< orphan*/  NFE_RX_PAUSE ; 
 int /*<<< orphan*/  NFE_RX_RUNT ; 
 int /*<<< orphan*/  NFE_RX_UNICAST ; 
 int /*<<< orphan*/  NFE_TX_BROADCAST ; 
 int /*<<< orphan*/  NFE_TX_CARRIER_LOST ; 
 int /*<<< orphan*/  NFE_TX_DEFERAL ; 
 int /*<<< orphan*/  NFE_TX_EXCESS_DEFERRAL ; 
 int /*<<< orphan*/  NFE_TX_FIFO_UNDERUN ; 
 int /*<<< orphan*/  NFE_TX_FRAME ; 
 int /*<<< orphan*/  NFE_TX_LATE_COL ; 
 int /*<<< orphan*/  NFE_TX_MULTICAST ; 
 int /*<<< orphan*/  NFE_TX_MULTI_REXMIT ; 
 int /*<<< orphan*/  NFE_TX_OCTET ; 
 int /*<<< orphan*/  NFE_TX_ONE_REXMIT ; 
 int /*<<< orphan*/  NFE_TX_PAUSE ; 
 int /*<<< orphan*/  NFE_TX_RETRY_ERROR ; 
 int /*<<< orphan*/  NFE_TX_UNICAST ; 
 int /*<<< orphan*/  NFE_TX_ZERO_REXMIT ; 

__attribute__((used)) static void
nfe_stats_update(struct nfe_softc *sc)
{
	struct nfe_hw_stats *stats;

	NFE_LOCK_ASSERT(sc);

	if ((sc->nfe_flags & (NFE_MIB_V1 | NFE_MIB_V2 | NFE_MIB_V3)) == 0)
		return;

	stats = &sc->nfe_stats;
	stats->tx_octets += NFE_READ(sc, NFE_TX_OCTET);
	stats->tx_zero_rexmits += NFE_READ(sc, NFE_TX_ZERO_REXMIT);
	stats->tx_one_rexmits += NFE_READ(sc, NFE_TX_ONE_REXMIT);
	stats->tx_multi_rexmits += NFE_READ(sc, NFE_TX_MULTI_REXMIT);
	stats->tx_late_cols += NFE_READ(sc, NFE_TX_LATE_COL);
	stats->tx_fifo_underuns += NFE_READ(sc, NFE_TX_FIFO_UNDERUN);
	stats->tx_carrier_losts += NFE_READ(sc, NFE_TX_CARRIER_LOST);
	stats->tx_excess_deferals += NFE_READ(sc, NFE_TX_EXCESS_DEFERRAL);
	stats->tx_retry_errors += NFE_READ(sc, NFE_TX_RETRY_ERROR);
	stats->rx_frame_errors += NFE_READ(sc, NFE_RX_FRAME_ERROR);
	stats->rx_extra_bytes += NFE_READ(sc, NFE_RX_EXTRA_BYTES);
	stats->rx_late_cols += NFE_READ(sc, NFE_RX_LATE_COL);
	stats->rx_runts += NFE_READ(sc, NFE_RX_RUNT);
	stats->rx_jumbos += NFE_READ(sc, NFE_RX_JUMBO);
	stats->rx_fifo_overuns += NFE_READ(sc, NFE_RX_FIFO_OVERUN);
	stats->rx_crc_errors += NFE_READ(sc, NFE_RX_CRC_ERROR);
	stats->rx_fae += NFE_READ(sc, NFE_RX_FAE);
	stats->rx_len_errors += NFE_READ(sc, NFE_RX_LEN_ERROR);
	stats->rx_unicast += NFE_READ(sc, NFE_RX_UNICAST);
	stats->rx_multicast += NFE_READ(sc, NFE_RX_MULTICAST);
	stats->rx_broadcast += NFE_READ(sc, NFE_RX_BROADCAST);

	if ((sc->nfe_flags & NFE_MIB_V2) != 0) {
		stats->tx_deferals += NFE_READ(sc, NFE_TX_DEFERAL);
		stats->tx_frames += NFE_READ(sc, NFE_TX_FRAME);
		stats->rx_octets += NFE_READ(sc, NFE_RX_OCTET);
		stats->tx_pause += NFE_READ(sc, NFE_TX_PAUSE);
		stats->rx_pause += NFE_READ(sc, NFE_RX_PAUSE);
		stats->rx_drops += NFE_READ(sc, NFE_RX_DROP);
	}

	if ((sc->nfe_flags & NFE_MIB_V3) != 0) {
		stats->tx_unicast += NFE_READ(sc, NFE_TX_UNICAST);
		stats->tx_multicast += NFE_READ(sc, NFE_TX_MULTICAST);
		stats->tx_broadcast += NFE_READ(sc, NFE_TX_BROADCAST);
	}
}