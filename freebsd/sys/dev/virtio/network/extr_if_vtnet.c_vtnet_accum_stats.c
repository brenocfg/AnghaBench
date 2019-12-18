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
struct vtnet_txq_stats {scalar_t__ vtxs_rescheduled; scalar_t__ vtxs_tso; scalar_t__ vtxs_csum; scalar_t__ vtxs_obytes; scalar_t__ vtxs_opackets; scalar_t__ vrxs_rescheduled; scalar_t__ vrxs_csum_failed; scalar_t__ vrxs_csum; scalar_t__ vrxs_iqdrops; scalar_t__ vrxs_ibytes; scalar_t__ vrxs_ipackets; } ;
struct vtnet_softc {int vtnet_max_vq_pairs; TYPE_2__* vtnet_txqs; TYPE_1__* vtnet_rxqs; } ;
struct vtnet_rxq_stats {scalar_t__ vtxs_rescheduled; scalar_t__ vtxs_tso; scalar_t__ vtxs_csum; scalar_t__ vtxs_obytes; scalar_t__ vtxs_opackets; scalar_t__ vrxs_rescheduled; scalar_t__ vrxs_csum_failed; scalar_t__ vrxs_csum; scalar_t__ vrxs_iqdrops; scalar_t__ vrxs_ibytes; scalar_t__ vrxs_ipackets; } ;
struct TYPE_4__ {struct vtnet_txq_stats vtntx_stats; } ;
struct TYPE_3__ {struct vtnet_txq_stats vtnrx_stats; } ;

/* Variables and functions */
 int /*<<< orphan*/  bzero (struct vtnet_txq_stats*,int) ; 

__attribute__((used)) static void
vtnet_accum_stats(struct vtnet_softc *sc, struct vtnet_rxq_stats *rxacc,
    struct vtnet_txq_stats *txacc)
{

	bzero(rxacc, sizeof(struct vtnet_rxq_stats));
	bzero(txacc, sizeof(struct vtnet_txq_stats));

	for (int i = 0; i < sc->vtnet_max_vq_pairs; i++) {
		struct vtnet_rxq_stats *rxst;
		struct vtnet_txq_stats *txst;

		rxst = &sc->vtnet_rxqs[i].vtnrx_stats;
		rxacc->vrxs_ipackets += rxst->vrxs_ipackets;
		rxacc->vrxs_ibytes += rxst->vrxs_ibytes;
		rxacc->vrxs_iqdrops += rxst->vrxs_iqdrops;
		rxacc->vrxs_csum += rxst->vrxs_csum;
		rxacc->vrxs_csum_failed += rxst->vrxs_csum_failed;
		rxacc->vrxs_rescheduled += rxst->vrxs_rescheduled;

		txst = &sc->vtnet_txqs[i].vtntx_stats;
		txacc->vtxs_opackets += txst->vtxs_opackets;
		txacc->vtxs_obytes += txst->vtxs_obytes;
		txacc->vtxs_csum += txst->vtxs_csum;
		txacc->vtxs_tso += txst->vtxs_tso;
		txacc->vtxs_rescheduled += txst->vtxs_rescheduled;
	}
}