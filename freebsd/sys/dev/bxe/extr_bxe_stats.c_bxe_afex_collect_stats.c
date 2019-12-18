#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ pmf; } ;
struct bxe_eth_stats {int /*<<< orphan*/  mac_discard; int /*<<< orphan*/  brb_truncate_discard; int /*<<< orphan*/  mac_filter_discard; } ;
struct bxe_softc {int num_queues; TYPE_2__ port; TYPE_1__* fp; struct bxe_eth_stats eth_stats; } ;
struct bxe_eth_q_stats {int /*<<< orphan*/  total_transmitted_dropped_packets_error_lo; int /*<<< orphan*/  total_transmitted_dropped_packets_error_hi; int /*<<< orphan*/  total_multicast_packets_transmitted_lo; int /*<<< orphan*/  total_multicast_packets_transmitted_hi; int /*<<< orphan*/  total_broadcast_packets_transmitted_lo; int /*<<< orphan*/  total_broadcast_packets_transmitted_hi; int /*<<< orphan*/  total_unicast_packets_transmitted_lo; int /*<<< orphan*/  total_unicast_packets_transmitted_hi; int /*<<< orphan*/  total_multicast_bytes_transmitted_lo; int /*<<< orphan*/  total_multicast_bytes_transmitted_hi; int /*<<< orphan*/  total_broadcast_bytes_transmitted_lo; int /*<<< orphan*/  total_broadcast_bytes_transmitted_hi; int /*<<< orphan*/  total_unicast_bytes_transmitted_lo; int /*<<< orphan*/  total_unicast_bytes_transmitted_hi; int /*<<< orphan*/  no_buff_discard_lo; int /*<<< orphan*/  no_buff_discard_hi; int /*<<< orphan*/  etherstatsoverrsizepkts_lo; int /*<<< orphan*/  etherstatsoverrsizepkts_hi; int /*<<< orphan*/  total_packets_received_ttl0_discarded_lo; int /*<<< orphan*/  total_packets_received_ttl0_discarded_hi; int /*<<< orphan*/  total_packets_received_checksum_discarded_lo; int /*<<< orphan*/  total_packets_received_checksum_discarded_hi; int /*<<< orphan*/  total_multicast_packets_received_lo; int /*<<< orphan*/  total_multicast_packets_received_hi; int /*<<< orphan*/  total_broadcast_packets_received_lo; int /*<<< orphan*/  total_broadcast_packets_received_hi; int /*<<< orphan*/  total_unicast_packets_received_lo; int /*<<< orphan*/  total_unicast_packets_received_hi; int /*<<< orphan*/  total_multicast_bytes_received_lo; int /*<<< orphan*/  total_multicast_bytes_received_hi; int /*<<< orphan*/  total_broadcast_bytes_received_lo; int /*<<< orphan*/  total_broadcast_bytes_received_hi; int /*<<< orphan*/  total_unicast_bytes_received_lo; int /*<<< orphan*/  total_unicast_bytes_received_hi; } ;
struct afex_stats {int /*<<< orphan*/  rx_frames_discarded_lo; int /*<<< orphan*/  rx_frames_discarded_hi; int /*<<< orphan*/  rx_frames_dropped_lo; int /*<<< orphan*/  rx_frames_dropped_hi; int /*<<< orphan*/  tx_frames_dropped_lo; int /*<<< orphan*/  tx_frames_dropped_hi; int /*<<< orphan*/  tx_multicast_frames_lo; int /*<<< orphan*/  tx_multicast_frames_hi; int /*<<< orphan*/  tx_broadcast_frames_lo; int /*<<< orphan*/  tx_broadcast_frames_hi; int /*<<< orphan*/  tx_unicast_frames_lo; int /*<<< orphan*/  tx_unicast_frames_hi; int /*<<< orphan*/  tx_multicast_bytes_lo; int /*<<< orphan*/  tx_multicast_bytes_hi; int /*<<< orphan*/  tx_broadcast_bytes_lo; int /*<<< orphan*/  tx_broadcast_bytes_hi; int /*<<< orphan*/  tx_unicast_bytes_lo; int /*<<< orphan*/  tx_unicast_bytes_hi; int /*<<< orphan*/  rx_multicast_frames_lo; int /*<<< orphan*/  rx_multicast_frames_hi; int /*<<< orphan*/  rx_broadcast_frames_lo; int /*<<< orphan*/  rx_broadcast_frames_hi; int /*<<< orphan*/  rx_unicast_frames_lo; int /*<<< orphan*/  rx_unicast_frames_hi; int /*<<< orphan*/  rx_multicast_bytes_lo; int /*<<< orphan*/  rx_multicast_bytes_hi; int /*<<< orphan*/  rx_broadcast_bytes_lo; int /*<<< orphan*/  rx_broadcast_bytes_hi; int /*<<< orphan*/  rx_unicast_bytes_lo; int /*<<< orphan*/  rx_unicast_bytes_hi; } ;
struct TYPE_3__ {struct bxe_eth_q_stats eth_q_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADD_64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ VICSTATST_UIF_INDEX ; 
 int /*<<< orphan*/  memset (struct afex_stats*,int /*<<< orphan*/ ,int) ; 

void
bxe_afex_collect_stats(struct bxe_softc *sc,
                       void             *void_afex_stats,
                       uint32_t         stats_type)
{
    int i;
    struct afex_stats *afex_stats = (struct afex_stats *)void_afex_stats;
    struct bxe_eth_stats *estats = &sc->eth_stats;

    memset(afex_stats, 0, sizeof(struct afex_stats));

    for (i = 0; i < sc->num_queues; i++) {
        struct bxe_eth_q_stats *qstats = &sc->fp[i].eth_q_stats;

        ADD_64(afex_stats->rx_unicast_bytes_hi,
               qstats->total_unicast_bytes_received_hi,
               afex_stats->rx_unicast_bytes_lo,
               qstats->total_unicast_bytes_received_lo);

        ADD_64(afex_stats->rx_broadcast_bytes_hi,
               qstats->total_broadcast_bytes_received_hi,
               afex_stats->rx_broadcast_bytes_lo,
               qstats->total_broadcast_bytes_received_lo);

        ADD_64(afex_stats->rx_multicast_bytes_hi,
               qstats->total_multicast_bytes_received_hi,
               afex_stats->rx_multicast_bytes_lo,
               qstats->total_multicast_bytes_received_lo);

        ADD_64(afex_stats->rx_unicast_frames_hi,
               qstats->total_unicast_packets_received_hi,
               afex_stats->rx_unicast_frames_lo,
               qstats->total_unicast_packets_received_lo);

        ADD_64(afex_stats->rx_broadcast_frames_hi,
               qstats->total_broadcast_packets_received_hi,
               afex_stats->rx_broadcast_frames_lo,
               qstats->total_broadcast_packets_received_lo);

        ADD_64(afex_stats->rx_multicast_frames_hi,
               qstats->total_multicast_packets_received_hi,
               afex_stats->rx_multicast_frames_lo,
               qstats->total_multicast_packets_received_lo);

        /*
         * sum to rx_frames_discarded all discarded
         * packets due to size, ttl0 and checksum
         */
        ADD_64(afex_stats->rx_frames_discarded_hi,
               qstats->total_packets_received_checksum_discarded_hi,
               afex_stats->rx_frames_discarded_lo,
               qstats->total_packets_received_checksum_discarded_lo);

        ADD_64(afex_stats->rx_frames_discarded_hi,
               qstats->total_packets_received_ttl0_discarded_hi,
               afex_stats->rx_frames_discarded_lo,
               qstats->total_packets_received_ttl0_discarded_lo);

        ADD_64(afex_stats->rx_frames_discarded_hi,
               qstats->etherstatsoverrsizepkts_hi,
               afex_stats->rx_frames_discarded_lo,
               qstats->etherstatsoverrsizepkts_lo);

        ADD_64(afex_stats->rx_frames_dropped_hi,
               qstats->no_buff_discard_hi,
               afex_stats->rx_frames_dropped_lo,
               qstats->no_buff_discard_lo);

        ADD_64(afex_stats->tx_unicast_bytes_hi,
               qstats->total_unicast_bytes_transmitted_hi,
               afex_stats->tx_unicast_bytes_lo,
               qstats->total_unicast_bytes_transmitted_lo);

        ADD_64(afex_stats->tx_broadcast_bytes_hi,
               qstats->total_broadcast_bytes_transmitted_hi,
               afex_stats->tx_broadcast_bytes_lo,
               qstats->total_broadcast_bytes_transmitted_lo);

        ADD_64(afex_stats->tx_multicast_bytes_hi,
               qstats->total_multicast_bytes_transmitted_hi,
               afex_stats->tx_multicast_bytes_lo,
               qstats->total_multicast_bytes_transmitted_lo);

        ADD_64(afex_stats->tx_unicast_frames_hi,
               qstats->total_unicast_packets_transmitted_hi,
               afex_stats->tx_unicast_frames_lo,
               qstats->total_unicast_packets_transmitted_lo);

        ADD_64(afex_stats->tx_broadcast_frames_hi,
               qstats->total_broadcast_packets_transmitted_hi,
               afex_stats->tx_broadcast_frames_lo,
               qstats->total_broadcast_packets_transmitted_lo);

        ADD_64(afex_stats->tx_multicast_frames_hi,
               qstats->total_multicast_packets_transmitted_hi,
               afex_stats->tx_multicast_frames_lo,
               qstats->total_multicast_packets_transmitted_lo);

        ADD_64(afex_stats->tx_frames_dropped_hi,
               qstats->total_transmitted_dropped_packets_error_hi,
               afex_stats->tx_frames_dropped_lo,
               qstats->total_transmitted_dropped_packets_error_lo);
    }

    /*
     * If port stats are requested, add them to the PMF
     * stats, as anyway they will be accumulated by the
     * MCP before sent to the switch
     */
    if ((sc->port.pmf) && (stats_type == VICSTATST_UIF_INDEX)) {
        ADD_64(afex_stats->rx_frames_dropped_hi,
               0,
               afex_stats->rx_frames_dropped_lo,
               estats->mac_filter_discard);
        ADD_64(afex_stats->rx_frames_dropped_hi,
               0,
               afex_stats->rx_frames_dropped_lo,
               estats->brb_truncate_discard);
        ADD_64(afex_stats->rx_frames_discarded_hi,
               0,
               afex_stats->rx_frames_discarded_lo,
               estats->mac_discard);
    }
}