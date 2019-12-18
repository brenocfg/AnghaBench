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
struct tx_ring {int tx_cidx_processed; int /*<<< orphan*/ * tx_rsq; int /*<<< orphan*/  tx_rs_pidx; int /*<<< orphan*/  tx_rs_cidx; } ;
struct ixl_vsi {int num_tx_queues; struct ixl_tx_queue* tx_queues; TYPE_1__* shared; } ;
struct ixl_tx_queue {struct tx_ring txr; } ;
typedef  TYPE_1__* if_softc_ctx_t ;
struct TYPE_2__ {int* isc_ntxd; } ;

/* Variables and functions */
 int /*<<< orphan*/  QIDX_INVALID ; 

void
ixl_init_tx_rsqs(struct ixl_vsi *vsi)
{
	if_softc_ctx_t scctx = vsi->shared;
	struct ixl_tx_queue *tx_que;
	int i, j;

	for (i = 0, tx_que = vsi->tx_queues; i < vsi->num_tx_queues; i++, tx_que++) {
		struct tx_ring *txr = &tx_que->txr;

		txr->tx_rs_cidx = txr->tx_rs_pidx;

		/* Initialize the last processed descriptor to be the end of
		 * the ring, rather than the start, so that we avoid an
		 * off-by-one error when calculating how many descriptors are
		 * done in the credits_update function.
		 */
		txr->tx_cidx_processed = scctx->isc_ntxd[0] - 1;

		for (j = 0; j < scctx->isc_ntxd[0]; j++)
			txr->tx_rsq[j] = QIDX_INVALID;
	}
}