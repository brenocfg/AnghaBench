#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct oce_tx_stats {int dummy; } ;
struct oce_rx_stats {int dummy; } ;
struct TYPE_13__ {int /*<<< orphan*/  t_ipv6_ext_hdr_tx_drop; int /*<<< orphan*/  t_tx_pkts; int /*<<< orphan*/  t_tx_bytes; int /*<<< orphan*/  t_tx_compl; int /*<<< orphan*/  t_tx_wrbs; int /*<<< orphan*/  t_tx_stops; int /*<<< orphan*/  t_tx_reqs; int /*<<< orphan*/  t_rxcp_errs; int /*<<< orphan*/  t_rx_ucast_pkts; int /*<<< orphan*/  t_rx_mcast_pkts; int /*<<< orphan*/  t_rx_frags; int /*<<< orphan*/  t_rx_bytes; int /*<<< orphan*/  t_rx_pkts; } ;
struct oce_drv_stats {TYPE_7__ tx; TYPE_7__ rx; } ;
struct TYPE_12__ {int nrqs; int nwqs; TYPE_4__** wq; TYPE_2__** rq; struct oce_drv_stats oce_stats_info; } ;
struct TYPE_10__ {scalar_t__ ipv6_ext_hdr_tx_drop; scalar_t__ tx_pkts; scalar_t__ tx_bytes; scalar_t__ tx_compl; scalar_t__ tx_wrbs; scalar_t__ tx_stops; scalar_t__ tx_reqs; } ;
struct TYPE_11__ {TYPE_3__ tx_stats; } ;
struct TYPE_8__ {scalar_t__ rxcp_err; scalar_t__ rx_ucast_pkts; scalar_t__ rx_mcast_pkts; scalar_t__ rx_frags; scalar_t__ rx_bytes; scalar_t__ rx_pkts; } ;
struct TYPE_9__ {TYPE_1__ rx_stats; } ;
typedef  TYPE_5__* POCE_SOFTC ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (TYPE_7__*,int) ; 

void 
oce_refresh_queue_stats(POCE_SOFTC sc)
{
	struct oce_drv_stats *adapter_stats;
	int i;

	adapter_stats = &sc->oce_stats_info;
	
	/* Caluculate total TX and TXstats from all queues */
	
	bzero(&adapter_stats->rx, sizeof(struct oce_rx_stats));
	for (i = 0; i < sc->nrqs; i++) {
		
		adapter_stats->rx.t_rx_pkts += sc->rq[i]->rx_stats.rx_pkts;
		adapter_stats->rx.t_rx_bytes += sc->rq[i]->rx_stats.rx_bytes;
		adapter_stats->rx.t_rx_frags += sc->rq[i]->rx_stats.rx_frags;
		adapter_stats->rx.t_rx_mcast_pkts += 
					sc->rq[i]->rx_stats.rx_mcast_pkts;
		adapter_stats->rx.t_rx_ucast_pkts +=
					sc->rq[i]->rx_stats.rx_ucast_pkts;
		adapter_stats->rx.t_rxcp_errs += sc-> rq[i]->rx_stats.rxcp_err;
	}

	bzero(&adapter_stats->tx, sizeof(struct oce_tx_stats));
	for (i = 0; i < sc->nwqs; i++) {
		adapter_stats->tx.t_tx_reqs += sc->wq[i]->tx_stats.tx_reqs;
		adapter_stats->tx.t_tx_stops += sc->wq[i]->tx_stats.tx_stops;
		adapter_stats->tx.t_tx_wrbs += sc->wq[i]->tx_stats.tx_wrbs;
		adapter_stats->tx.t_tx_compl += sc->wq[i]->tx_stats.tx_compl;
		adapter_stats->tx.t_tx_bytes += sc->wq[i]->tx_stats.tx_bytes;
		adapter_stats->tx.t_tx_pkts += sc->wq[i]->tx_stats.tx_pkts;
		adapter_stats->tx.t_ipv6_ext_hdr_tx_drop +=
				sc->wq[i]->tx_stats.ipv6_ext_hdr_tx_drop;
	}

}