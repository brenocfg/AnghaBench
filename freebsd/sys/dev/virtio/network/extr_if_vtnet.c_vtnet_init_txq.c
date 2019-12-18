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
struct vtnet_txq {int vtntx_id; int /*<<< orphan*/ * vtntx_tq; int /*<<< orphan*/  vtntx_name; int /*<<< orphan*/  vtntx_intrtask; int /*<<< orphan*/  vtntx_defrtask; int /*<<< orphan*/ * vtntx_br; int /*<<< orphan*/  vtntx_mtx; int /*<<< orphan*/ * vtntx_sg; struct vtnet_softc* vtntx_sc; } ;
struct vtnet_softc {int /*<<< orphan*/  vtnet_tx_nsegs; int /*<<< orphan*/  vtnet_dev; struct vtnet_txq* vtnet_txqs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_DEVBUF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vtnet_txq*) ; 
 int /*<<< orphan*/  VTNET_DEFAULT_BUFRING_SIZE ; 
 int /*<<< orphan*/ * buf_ring_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sglist_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  vtnet_txq_tq_deferred ; 
 int /*<<< orphan*/  vtnet_txq_tq_intr ; 

__attribute__((used)) static int
vtnet_init_txq(struct vtnet_softc *sc, int id)
{
	struct vtnet_txq *txq;

	txq = &sc->vtnet_txqs[id];

	snprintf(txq->vtntx_name, sizeof(txq->vtntx_name), "%s-tx%d",
	    device_get_nameunit(sc->vtnet_dev), id);
	mtx_init(&txq->vtntx_mtx, txq->vtntx_name, NULL, MTX_DEF);

	txq->vtntx_sc = sc;
	txq->vtntx_id = id;

	txq->vtntx_sg = sglist_alloc(sc->vtnet_tx_nsegs, M_NOWAIT);
	if (txq->vtntx_sg == NULL)
		return (ENOMEM);

#ifndef VTNET_LEGACY_TX
	txq->vtntx_br = buf_ring_alloc(VTNET_DEFAULT_BUFRING_SIZE, M_DEVBUF,
	    M_NOWAIT, &txq->vtntx_mtx);
	if (txq->vtntx_br == NULL)
		return (ENOMEM);

	TASK_INIT(&txq->vtntx_defrtask, 0, vtnet_txq_tq_deferred, txq);
#endif
	TASK_INIT(&txq->vtntx_intrtask, 0, vtnet_txq_tq_intr, txq);
	txq->vtntx_tq = taskqueue_create(txq->vtntx_name, M_NOWAIT,
	    taskqueue_thread_enqueue, &txq->vtntx_tq);
	if (txq->vtntx_tq == NULL)
		return (ENOMEM);

	return (0);
}