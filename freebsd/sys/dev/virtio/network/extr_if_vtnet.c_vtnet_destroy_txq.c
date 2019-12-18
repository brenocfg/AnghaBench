#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct vtnet_txq {int vtntx_id; int /*<<< orphan*/  vtntx_mtx; int /*<<< orphan*/ * vtntx_br; int /*<<< orphan*/ * vtntx_sg; int /*<<< orphan*/ * vtntx_sc; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  buf_ring_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 scalar_t__ mtx_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vtnet_destroy_txq(struct vtnet_txq *txq)
{

	txq->vtntx_sc = NULL;
	txq->vtntx_id = -1;

	if (txq->vtntx_sg != NULL) {
		sglist_free(txq->vtntx_sg);
		txq->vtntx_sg = NULL;
	}

#ifndef VTNET_LEGACY_TX
	if (txq->vtntx_br != NULL) {
		buf_ring_free(txq->vtntx_br, M_DEVBUF);
		txq->vtntx_br = NULL;
	}
#endif

	if (mtx_initialized(&txq->vtntx_mtx) != 0)
		mtx_destroy(&txq->vtntx_mtx);
}