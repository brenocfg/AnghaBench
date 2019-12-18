#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ status_error; } ;
struct TYPE_9__ {TYPE_2__ upper; } ;
struct TYPE_7__ {int /*<<< orphan*/  buffer_addr; } ;
union e1000_rx_desc_extended {TYPE_3__ wb; TYPE_1__ read; } ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  size_t uint16_t ;
struct rx_ring {union e1000_rx_desc_extended* rx_base; } ;
struct em_rx_queue {struct rx_ring rxr; } ;
struct adapter {struct em_rx_queue* rx_queues; TYPE_4__* shared; } ;
typedef  TYPE_4__* if_softc_ctx_t ;
typedef  TYPE_5__* if_rxd_update_t ;
struct TYPE_11__ {size_t iru_qsidx; size_t iru_pidx; size_t iru_count; int /*<<< orphan*/ * iru_paddrs; } ;
struct TYPE_10__ {size_t* isc_nrxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
em_isc_rxd_refill(void *arg, if_rxd_update_t iru)
{
	struct adapter *sc = arg;
	if_softc_ctx_t scctx = sc->shared;
	uint16_t rxqid = iru->iru_qsidx;
	struct em_rx_queue *que = &sc->rx_queues[rxqid];
	struct rx_ring *rxr = &que->rxr;
	union e1000_rx_desc_extended *rxd;
	uint64_t *paddrs;
	uint32_t next_pidx, pidx;
	uint16_t count;
	int i;

	paddrs = iru->iru_paddrs;
	pidx = iru->iru_pidx;
	count = iru->iru_count;

	for (i = 0, next_pidx = pidx; i < count; i++) {
		rxd = &rxr->rx_base[next_pidx];
		rxd->read.buffer_addr = htole64(paddrs[i]);
		/* DD bits must be cleared */
		rxd->wb.upper.status_error = 0;

		if (++next_pidx == scctx->isc_nrxd[0])
			next_pidx = 0;
	}
}