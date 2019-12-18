#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* iflib_txq_t ;
typedef  TYPE_2__* if_shared_ctx_t ;
typedef  TYPE_3__* if_ctx_t ;
struct TYPE_11__ {TYPE_1__* ifc_txqs; TYPE_2__* ifc_sctx; } ;
struct TYPE_10__ {int isc_ntxqs; } ;
struct TYPE_9__ {int /*<<< orphan*/ * ift_ifdi; } ;

/* Variables and functions */
 int /*<<< orphan*/  IFDI_QUEUES_FREE (TYPE_3__*) ; 
 int /*<<< orphan*/  M_IFLIB ; 
 int NTXQSETS (TYPE_3__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iflib_dma_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iflib_txq_destroy (TYPE_1__*) ; 

__attribute__((used)) static void
iflib_tx_structures_free(if_ctx_t ctx)
{
	iflib_txq_t txq = ctx->ifc_txqs;
	if_shared_ctx_t sctx = ctx->ifc_sctx;
	int i, j;

	for (i = 0; i < NTXQSETS(ctx); i++, txq++) {
		for (j = 0; j < sctx->isc_ntxqs; j++)
			iflib_dma_free(&txq->ift_ifdi[j]);
		iflib_txq_destroy(txq);
	}
	free(ctx->ifc_txqs, M_IFLIB);
	ctx->ifc_txqs = NULL;
	IFDI_QUEUES_FREE(ctx);
}