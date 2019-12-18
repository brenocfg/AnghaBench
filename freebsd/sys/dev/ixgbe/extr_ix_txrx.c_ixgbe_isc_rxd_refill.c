#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
typedef  size_t uint32_t ;
typedef  int uint16_t ;
struct rx_ring {TYPE_2__* rx_base; } ;
struct ix_rx_queue {struct rx_ring rxr; } ;
struct adapter {TYPE_3__* shared; struct ix_rx_queue* rx_queues; } ;
typedef  TYPE_4__* if_rxd_update_t ;
struct TYPE_9__ {size_t iru_qsidx; size_t iru_pidx; int iru_count; int /*<<< orphan*/ * iru_paddrs; } ;
struct TYPE_8__ {size_t* isc_nrxd; } ;
struct TYPE_6__ {int /*<<< orphan*/  pkt_addr; } ;
struct TYPE_7__ {TYPE_1__ read; } ;

/* Variables and functions */
 int /*<<< orphan*/  htole64 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ixgbe_isc_rxd_refill(void *arg, if_rxd_update_t iru)
{
	struct adapter *sc       = arg;
	struct ix_rx_queue *que  = &sc->rx_queues[iru->iru_qsidx];
	struct rx_ring *rxr      = &que->rxr;
	uint64_t *paddrs;
	int i;
	uint32_t next_pidx, pidx;
	uint16_t count;

	paddrs = iru->iru_paddrs;
	pidx = iru->iru_pidx;
	count = iru->iru_count;

	for (i = 0, next_pidx = pidx; i < count; i++) {
		rxr->rx_base[next_pidx].read.pkt_addr = htole64(paddrs[i]);
		if (++next_pidx == sc->shared->isc_nrxd[0])
			next_pidx = 0;
	}
}