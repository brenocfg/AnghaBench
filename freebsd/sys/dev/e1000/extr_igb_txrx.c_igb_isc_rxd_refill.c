#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  pkt_addr; } ;
union e1000_adv_rx_desc {TYPE_1__ read; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct rx_ring {int /*<<< orphan*/ * rx_base; } ;
struct em_rx_queue {struct rx_ring rxr; } ;
struct adapter {struct em_rx_queue* rx_queues; TYPE_2__* shared; } ;
typedef  TYPE_2__* if_softc_ctx_t ;
typedef  TYPE_3__* if_rxd_update_t ;
struct TYPE_7__ {size_t iru_qsidx; size_t iru_pidx; size_t iru_count; int /*<<< orphan*/ * iru_paddrs; } ;
struct TYPE_6__ {size_t* isc_nrxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
igb_isc_rxd_refill(void *arg, if_rxd_update_t iru)
{
	struct adapter *sc = arg;
	if_softc_ctx_t scctx = sc->shared;
	uint16_t rxqid = iru->iru_qsidx;
	struct em_rx_queue *que = &sc->rx_queues[rxqid];
	union e1000_adv_rx_desc *rxd;
	struct rx_ring *rxr = &que->rxr;
	uint64_t *paddrs;
	uint32_t next_pidx, pidx;
	uint16_t count;
	int i;

	paddrs = iru->iru_paddrs;
	pidx = iru->iru_pidx;
	count = iru->iru_count;

	for (i = 0, next_pidx = pidx; i < count; i++) {
		rxd = (union e1000_adv_rx_desc *)&rxr->rx_base[next_pidx];

		rxd->read.pkt_addr = htole64(paddrs[i]);
		if (++next_pidx == scctx->isc_nrxd[0])
			next_pidx = 0;
	}
}