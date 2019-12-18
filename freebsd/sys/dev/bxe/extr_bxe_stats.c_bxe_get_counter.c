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
struct bxe_eth_stats {int /*<<< orphan*/  tx_stat_dot3statsexcessivecollisions_hi; int /*<<< orphan*/  tx_stat_dot3statslatecollisions_hi; int /*<<< orphan*/  tx_stat_etherstatscollisions_hi; int /*<<< orphan*/  total_multicast_packets_received_hi; int /*<<< orphan*/  tx_stat_dot3statsinternalmactransmiterrors_hi; int /*<<< orphan*/  rx_stat_dot3statscarriersenseerrors_hi; int /*<<< orphan*/  no_buff_discard_hi; int /*<<< orphan*/  rx_stat_dot3statsalignmenterrors_hi; int /*<<< orphan*/  rx_stat_dot3statsfcserrors_hi; int /*<<< orphan*/  brb_truncate_hi; int /*<<< orphan*/  brb_drop_hi; int /*<<< orphan*/  etherstatsoverrsizepkts_hi; int /*<<< orphan*/  rx_stat_etherstatsundersizepkts_hi; int /*<<< orphan*/  total_bytes_transmitted_hi; int /*<<< orphan*/  total_bytes_received_hi; int /*<<< orphan*/  total_broadcast_packets_transmitted_hi; int /*<<< orphan*/  total_multicast_packets_transmitted_hi; int /*<<< orphan*/  total_unicast_packets_transmitted_hi; int /*<<< orphan*/  total_broadcast_packets_received_hi; int /*<<< orphan*/  total_unicast_packets_received_hi; } ;
struct bxe_softc {struct bxe_eth_stats eth_stats; } ;
typedef  int ift_counter ;
typedef  int /*<<< orphan*/  if_t ;

/* Variables and functions */
#define  IFCOUNTER_COLLISIONS 135 
#define  IFCOUNTER_IBYTES 134 
#define  IFCOUNTER_IERRORS 133 
#define  IFCOUNTER_IMCASTS 132 
#define  IFCOUNTER_IPACKETS 131 
#define  IFCOUNTER_OBYTES 130 
#define  IFCOUNTER_OERRORS 129 
#define  IFCOUNTER_OPACKETS 128 
 scalar_t__ bxe_hilo (int /*<<< orphan*/ *) ; 
 scalar_t__ if_get_counter_default (int /*<<< orphan*/ ,int) ; 
 struct bxe_softc* if_getsoftc (int /*<<< orphan*/ ) ; 

uint64_t
bxe_get_counter(if_t ifp, ift_counter cnt)
{
	struct bxe_softc *sc;
	struct bxe_eth_stats *estats;

	sc = if_getsoftc(ifp);
	estats = &sc->eth_stats;

	switch (cnt) {
	case IFCOUNTER_IPACKETS:
		return (bxe_hilo(&estats->total_unicast_packets_received_hi) +
		    bxe_hilo(&estats->total_multicast_packets_received_hi) +
		    bxe_hilo(&estats->total_broadcast_packets_received_hi));
	case IFCOUNTER_OPACKETS:
		return (bxe_hilo(&estats->total_unicast_packets_transmitted_hi) +
		    bxe_hilo(&estats->total_multicast_packets_transmitted_hi) +
		    bxe_hilo(&estats->total_broadcast_packets_transmitted_hi));
	case IFCOUNTER_IBYTES:
		return (bxe_hilo(&estats->total_bytes_received_hi));
	case IFCOUNTER_OBYTES:
		return (bxe_hilo(&estats->total_bytes_transmitted_hi));
	case IFCOUNTER_IERRORS:
		return (bxe_hilo(&estats->rx_stat_etherstatsundersizepkts_hi) +
		    bxe_hilo(&estats->etherstatsoverrsizepkts_hi) +
		    bxe_hilo(&estats->brb_drop_hi) +
		    bxe_hilo(&estats->brb_truncate_hi) +
		    bxe_hilo(&estats->rx_stat_dot3statsfcserrors_hi) +
		    bxe_hilo(&estats->rx_stat_dot3statsalignmenterrors_hi) +
		    bxe_hilo(&estats->no_buff_discard_hi));
	case IFCOUNTER_OERRORS:
		return (bxe_hilo(&estats->rx_stat_dot3statscarriersenseerrors_hi) +
		    bxe_hilo(&estats->tx_stat_dot3statsinternalmactransmiterrors_hi));
	case IFCOUNTER_IMCASTS:
		return (bxe_hilo(&estats->total_multicast_packets_received_hi));
	case IFCOUNTER_COLLISIONS:
		return (bxe_hilo(&estats->tx_stat_etherstatscollisions_hi) +
		    bxe_hilo(&estats->tx_stat_dot3statslatecollisions_hi) +
		    bxe_hilo(&estats->tx_stat_dot3statsexcessivecollisions_hi));
	default:
		return (if_get_counter_default(ifp, cnt));
	}
}