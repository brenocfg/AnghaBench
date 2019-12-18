#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct tx_ring {scalar_t__ tx_cidx_processed; } ;
struct ixl_vsi {int num_tx_queues; struct ixl_tx_queue* tx_queues; TYPE_1__* shared; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {scalar_t__* isc_ntxd; } ;

/* Variables and functions */

void
ixl_init_tx_cidx(struct ixl_vsi *vsi)
{
	if_softc_ctx_t scctx = vsi->shared;
	struct ixl_tx_queue *tx_que;
	int i;
	
	for (i = 0, tx_que = vsi->tx_queues; i < vsi->num_tx_queues; i++, tx_que++) {
		struct tx_ring *txr = &tx_que->txr;

		txr->tx_cidx_processed = scctx->isc_ntxd[0] - 1;
	}
}