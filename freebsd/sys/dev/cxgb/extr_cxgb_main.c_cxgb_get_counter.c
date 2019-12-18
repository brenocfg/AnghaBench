#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct mac_stats {scalar_t__ rx_cong_drops; scalar_t__ tx_mcast_frames; scalar_t__ rx_mcast_frames; scalar_t__ tx_octets; scalar_t__ rx_octets; scalar_t__ tx_total_collisions; scalar_t__ tx_fcs_errs; scalar_t__ tx_excess_deferral; scalar_t__ tx_mac_internal_errs; scalar_t__ tx_len_errs; scalar_t__ tx_underrun; scalar_t__ tx_excess_collisions; scalar_t__ tx_frames; scalar_t__ rx_fcs_errs; scalar_t__ rx_short; scalar_t__ rx_mac_internal_errs; scalar_t__ rx_too_long; scalar_t__ rx_runt; scalar_t__ rx_sequence_errs; scalar_t__ rx_data_errs; scalar_t__ rx_jabber; scalar_t__ rx_frames; } ;
struct cmac {struct mac_stats stats; } ;
struct port_info {int first_qset; int nqsets; struct cmac mac; struct adapter* adapter; } ;
struct ifnet {struct port_info* if_softc; } ;
struct TYPE_8__ {TYPE_3__* qs; } ;
struct adapter {int flags; TYPE_4__ sge; } ;
typedef  int ift_counter ;
struct TYPE_7__ {TYPE_2__* txq; } ;
struct TYPE_6__ {TYPE_1__* txq_mr; } ;
struct TYPE_5__ {scalar_t__ br_drops; } ;

/* Variables and functions */
 int FULL_INIT_DONE ; 
#define  IFCOUNTER_COLLISIONS 138 
#define  IFCOUNTER_IBYTES 137 
#define  IFCOUNTER_IERRORS 136 
#define  IFCOUNTER_IMCASTS 135 
#define  IFCOUNTER_IPACKETS 134 
#define  IFCOUNTER_IQDROPS 133 
#define  IFCOUNTER_OBYTES 132 
#define  IFCOUNTER_OERRORS 131 
#define  IFCOUNTER_OMCASTS 130 
#define  IFCOUNTER_OPACKETS 129 
#define  IFCOUNTER_OQDROPS 128 
 size_t TXQ_ETH ; 
 int /*<<< orphan*/  cxgb_refresh_stats (struct port_info*) ; 
 scalar_t__ if_get_counter_default (struct ifnet*,int) ; 

__attribute__((used)) static uint64_t
cxgb_get_counter(struct ifnet *ifp, ift_counter c)
{
	struct port_info *pi = ifp->if_softc;
	struct adapter *sc = pi->adapter;
	struct cmac *mac = &pi->mac;
	struct mac_stats *mstats = &mac->stats;

	cxgb_refresh_stats(pi);

	switch (c) {
	case IFCOUNTER_IPACKETS:
		return (mstats->rx_frames);

	case IFCOUNTER_IERRORS:
		return (mstats->rx_jabber + mstats->rx_data_errs +
		    mstats->rx_sequence_errs + mstats->rx_runt +
		    mstats->rx_too_long + mstats->rx_mac_internal_errs +
		    mstats->rx_short + mstats->rx_fcs_errs);

	case IFCOUNTER_OPACKETS:
		return (mstats->tx_frames);

	case IFCOUNTER_OERRORS:
		return (mstats->tx_excess_collisions + mstats->tx_underrun +
		    mstats->tx_len_errs + mstats->tx_mac_internal_errs +
		    mstats->tx_excess_deferral + mstats->tx_fcs_errs);

	case IFCOUNTER_COLLISIONS:
		return (mstats->tx_total_collisions);

	case IFCOUNTER_IBYTES:
		return (mstats->rx_octets);

	case IFCOUNTER_OBYTES:
		return (mstats->tx_octets);

	case IFCOUNTER_IMCASTS:
		return (mstats->rx_mcast_frames);

	case IFCOUNTER_OMCASTS:
		return (mstats->tx_mcast_frames);

	case IFCOUNTER_IQDROPS:
		return (mstats->rx_cong_drops);

	case IFCOUNTER_OQDROPS: {
		int i;
		uint64_t drops;

		drops = 0;
		if (sc->flags & FULL_INIT_DONE) {
			for (i = pi->first_qset; i < pi->first_qset + pi->nqsets; i++)
				drops += sc->sge.qs[i].txq[TXQ_ETH].txq_mr->br_drops;
		}

		return (drops);

	}

	default:
		return (if_get_counter_default(ifp, c));
	}
}