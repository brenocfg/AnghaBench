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
typedef  int uint8_t ;
struct tx_ring {size_t tx_rs_cidx; size_t tx_rs_pidx; size_t* tx_rsq; int tx_cidx_processed; TYPE_3__* tx_base; } ;
struct em_tx_queue {struct tx_ring txr; } ;
struct adapter {size_t tx_num_queues; struct em_tx_queue* tx_queues; TYPE_4__* shared; } ;
typedef  size_t qidx_t ;
typedef  size_t int16_t ;
typedef  TYPE_4__* if_softc_ctx_t ;
struct TYPE_8__ {size_t* isc_ntxd; } ;
struct TYPE_5__ {int status; } ;
struct TYPE_6__ {TYPE_1__ fields; } ;
struct TYPE_7__ {TYPE_2__ upper; } ;

/* Variables and functions */
 int E1000_TXD_STAT_DD ; 
 int /*<<< orphan*/  printf (char*,...) ; 

void
em_dump_rs(struct adapter *adapter)
{
	if_softc_ctx_t scctx = adapter->shared;
	struct em_tx_queue *que;
	struct tx_ring *txr;
	qidx_t i, ntxd, qid, cur;
	int16_t rs_cidx;
	uint8_t status;

	printf("\n");
	ntxd = scctx->isc_ntxd[0];
	for (qid = 0; qid < adapter->tx_num_queues; qid++) {
		que = &adapter->tx_queues[qid];
		txr =  &que->txr;
		rs_cidx = txr->tx_rs_cidx;
		if (rs_cidx != txr->tx_rs_pidx) {
			cur = txr->tx_rsq[rs_cidx];
			status = txr->tx_base[cur].upper.fields.status;
			if (!(status & E1000_TXD_STAT_DD))
				printf("qid[%d]->tx_rsq[%d]: %d clear ", qid, rs_cidx, cur);
		} else {
			rs_cidx = (rs_cidx-1)&(ntxd-1);
			cur = txr->tx_rsq[rs_cidx];
			printf("qid[%d]->tx_rsq[rs_cidx-1=%d]: %d  ", qid, rs_cidx, cur);
		}
		printf("cidx_prev=%d rs_pidx=%d ",txr->tx_cidx_processed, txr->tx_rs_pidx);
		for (i = 0; i < ntxd; i++) {
			if (txr->tx_base[i].upper.fields.status & E1000_TXD_STAT_DD)
				printf("%d set ", i);
		}
		printf("\n");
	}
}