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
struct et_hw_stats {int /*<<< orphan*/  tx_fragments; int /*<<< orphan*/  tx_undersize; int /*<<< orphan*/  tx_oversize; int /*<<< orphan*/  tx_control; int /*<<< orphan*/  tx_crcerrs; int /*<<< orphan*/  tx_jabbers; int /*<<< orphan*/  tx_drop; int /*<<< orphan*/  tx_pause_honored; int /*<<< orphan*/  tx_total_colls; int /*<<< orphan*/  tx_excess_colls; int /*<<< orphan*/  tx_late_colls; int /*<<< orphan*/  tx_multi_colls; int /*<<< orphan*/  tx_single_colls; int /*<<< orphan*/  tx_excess_deferred; int /*<<< orphan*/  tx_deferred; int /*<<< orphan*/  tx_pause; int /*<<< orphan*/  tx_bcast; int /*<<< orphan*/  tx_mcast; int /*<<< orphan*/  tx_frames; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  rx_drop; int /*<<< orphan*/  rx_jabbers; int /*<<< orphan*/  rx_fragments; int /*<<< orphan*/  rx_oversize; int /*<<< orphan*/  rx_runts; int /*<<< orphan*/  rx_cserrs; int /*<<< orphan*/  rx_codeerrs; int /*<<< orphan*/  rx_lenerrs; int /*<<< orphan*/  rx_alignerrs; int /*<<< orphan*/  rx_unknown_control; int /*<<< orphan*/  rx_pause; int /*<<< orphan*/  rx_control; int /*<<< orphan*/  rx_bcast; int /*<<< orphan*/  rx_mcast; int /*<<< orphan*/  rx_crcerrs; int /*<<< orphan*/  rx_frames; int /*<<< orphan*/  rx_bytes; int /*<<< orphan*/  pkts_1519; int /*<<< orphan*/  pkts_1024; int /*<<< orphan*/  pkts_512; int /*<<< orphan*/  pkts_256; int /*<<< orphan*/  pkts_128; int /*<<< orphan*/  pkts_65; int /*<<< orphan*/  pkts_64; } ;
struct et_softc {struct et_hw_stats sc_stats; } ;

/* Variables and functions */
 scalar_t__ CSR_READ_4 (struct et_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ET_STAT_PKTS_1024_1518 ; 
 int /*<<< orphan*/  ET_STAT_PKTS_128_255 ; 
 int /*<<< orphan*/  ET_STAT_PKTS_1519_1522 ; 
 int /*<<< orphan*/  ET_STAT_PKTS_256_511 ; 
 int /*<<< orphan*/  ET_STAT_PKTS_512_1023 ; 
 int /*<<< orphan*/  ET_STAT_PKTS_64 ; 
 int /*<<< orphan*/  ET_STAT_PKTS_65_127 ; 
 int /*<<< orphan*/  ET_STAT_RX_ALIGN_ERR ; 
 int /*<<< orphan*/  ET_STAT_RX_BCAST ; 
 int /*<<< orphan*/  ET_STAT_RX_BYTES ; 
 int /*<<< orphan*/  ET_STAT_RX_CODE_ERR ; 
 int /*<<< orphan*/  ET_STAT_RX_CRC_ERR ; 
 int /*<<< orphan*/  ET_STAT_RX_CS_ERR ; 
 int /*<<< orphan*/  ET_STAT_RX_CTL ; 
 int /*<<< orphan*/  ET_STAT_RX_DROP ; 
 int /*<<< orphan*/  ET_STAT_RX_FRAG ; 
 int /*<<< orphan*/  ET_STAT_RX_FRAMES ; 
 int /*<<< orphan*/  ET_STAT_RX_JABBER ; 
 int /*<<< orphan*/  ET_STAT_RX_LEN_ERR ; 
 int /*<<< orphan*/  ET_STAT_RX_MCAST ; 
 int /*<<< orphan*/  ET_STAT_RX_OVERSIZE ; 
 int /*<<< orphan*/  ET_STAT_RX_PAUSE ; 
 int /*<<< orphan*/  ET_STAT_RX_RUNT ; 
 int /*<<< orphan*/  ET_STAT_RX_UNKNOWN_CTL ; 
 int /*<<< orphan*/  ET_STAT_TX_BCAST ; 
 int /*<<< orphan*/  ET_STAT_TX_BYTES ; 
 int /*<<< orphan*/  ET_STAT_TX_CRC_ERR ; 
 int /*<<< orphan*/  ET_STAT_TX_CTL ; 
 int /*<<< orphan*/  ET_STAT_TX_DEFER ; 
 int /*<<< orphan*/  ET_STAT_TX_DROP ; 
 int /*<<< orphan*/  ET_STAT_TX_EXCESS_COL ; 
 int /*<<< orphan*/  ET_STAT_TX_EXCESS_DEFER ; 
 int /*<<< orphan*/  ET_STAT_TX_FRAG ; 
 int /*<<< orphan*/  ET_STAT_TX_FRAMES ; 
 int /*<<< orphan*/  ET_STAT_TX_JABBER ; 
 int /*<<< orphan*/  ET_STAT_TX_LATE_COL ; 
 int /*<<< orphan*/  ET_STAT_TX_MCAST ; 
 int /*<<< orphan*/  ET_STAT_TX_MULTI_COL ; 
 int /*<<< orphan*/  ET_STAT_TX_OVERSIZE ; 
 int /*<<< orphan*/  ET_STAT_TX_PAUSE ; 
 int /*<<< orphan*/  ET_STAT_TX_PAUSE_HONOR ; 
 int /*<<< orphan*/  ET_STAT_TX_SINGLE_COL ; 
 int /*<<< orphan*/  ET_STAT_TX_TOTAL_COL ; 
 int /*<<< orphan*/  ET_STAT_TX_UNDERSIZE ; 

__attribute__((used)) static void
et_stats_update(struct et_softc *sc)
{
	struct et_hw_stats *stats;

	stats = &sc->sc_stats;
	stats->pkts_64 += CSR_READ_4(sc, ET_STAT_PKTS_64);
	stats->pkts_65 += CSR_READ_4(sc, ET_STAT_PKTS_65_127);
	stats->pkts_128 += CSR_READ_4(sc, ET_STAT_PKTS_128_255);
	stats->pkts_256 += CSR_READ_4(sc, ET_STAT_PKTS_256_511);
	stats->pkts_512 += CSR_READ_4(sc, ET_STAT_PKTS_512_1023);
	stats->pkts_1024 += CSR_READ_4(sc, ET_STAT_PKTS_1024_1518);
	stats->pkts_1519 += CSR_READ_4(sc, ET_STAT_PKTS_1519_1522);

	stats->rx_bytes += CSR_READ_4(sc, ET_STAT_RX_BYTES);
	stats->rx_frames += CSR_READ_4(sc, ET_STAT_RX_FRAMES);
	stats->rx_crcerrs += CSR_READ_4(sc, ET_STAT_RX_CRC_ERR);
	stats->rx_mcast += CSR_READ_4(sc, ET_STAT_RX_MCAST);
	stats->rx_bcast += CSR_READ_4(sc, ET_STAT_RX_BCAST);
	stats->rx_control += CSR_READ_4(sc, ET_STAT_RX_CTL);
	stats->rx_pause += CSR_READ_4(sc, ET_STAT_RX_PAUSE);
	stats->rx_unknown_control += CSR_READ_4(sc, ET_STAT_RX_UNKNOWN_CTL);
	stats->rx_alignerrs += CSR_READ_4(sc, ET_STAT_RX_ALIGN_ERR);
	stats->rx_lenerrs += CSR_READ_4(sc, ET_STAT_RX_LEN_ERR);
	stats->rx_codeerrs += CSR_READ_4(sc, ET_STAT_RX_CODE_ERR);
	stats->rx_cserrs += CSR_READ_4(sc, ET_STAT_RX_CS_ERR);
	stats->rx_runts += CSR_READ_4(sc, ET_STAT_RX_RUNT);
	stats->rx_oversize += CSR_READ_4(sc, ET_STAT_RX_OVERSIZE);
	stats->rx_fragments += CSR_READ_4(sc, ET_STAT_RX_FRAG);
	stats->rx_jabbers += CSR_READ_4(sc, ET_STAT_RX_JABBER);
	stats->rx_drop += CSR_READ_4(sc, ET_STAT_RX_DROP);

	stats->tx_bytes += CSR_READ_4(sc, ET_STAT_TX_BYTES);
	stats->tx_frames += CSR_READ_4(sc, ET_STAT_TX_FRAMES);
	stats->tx_mcast += CSR_READ_4(sc, ET_STAT_TX_MCAST);
	stats->tx_bcast += CSR_READ_4(sc, ET_STAT_TX_BCAST);
	stats->tx_pause += CSR_READ_4(sc, ET_STAT_TX_PAUSE);
	stats->tx_deferred += CSR_READ_4(sc, ET_STAT_TX_DEFER);
	stats->tx_excess_deferred += CSR_READ_4(sc, ET_STAT_TX_EXCESS_DEFER);
	stats->tx_single_colls += CSR_READ_4(sc, ET_STAT_TX_SINGLE_COL);
	stats->tx_multi_colls += CSR_READ_4(sc, ET_STAT_TX_MULTI_COL);
	stats->tx_late_colls += CSR_READ_4(sc, ET_STAT_TX_LATE_COL);
	stats->tx_excess_colls += CSR_READ_4(sc, ET_STAT_TX_EXCESS_COL);
	stats->tx_total_colls += CSR_READ_4(sc, ET_STAT_TX_TOTAL_COL);
	stats->tx_pause_honored += CSR_READ_4(sc, ET_STAT_TX_PAUSE_HONOR);
	stats->tx_drop += CSR_READ_4(sc, ET_STAT_TX_DROP);
	stats->tx_jabbers += CSR_READ_4(sc, ET_STAT_TX_JABBER);
	stats->tx_crcerrs += CSR_READ_4(sc, ET_STAT_TX_CRC_ERR);
	stats->tx_control += CSR_READ_4(sc, ET_STAT_TX_CTL);
	stats->tx_oversize += CSR_READ_4(sc, ET_STAT_TX_OVERSIZE);
	stats->tx_undersize += CSR_READ_4(sc, ET_STAT_TX_UNDERSIZE);
	stats->tx_fragments += CSR_READ_4(sc, ET_STAT_TX_FRAG);
}