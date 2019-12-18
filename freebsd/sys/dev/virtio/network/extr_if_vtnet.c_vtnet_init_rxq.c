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
struct vtnet_softc {int /*<<< orphan*/  vtnet_rx_nsegs; int /*<<< orphan*/  vtnet_dev; struct vtnet_rxq* vtnet_rxqs; } ;
struct vtnet_rxq {int vtnrx_id; int /*<<< orphan*/ * vtnrx_tq; int /*<<< orphan*/  vtnrx_name; int /*<<< orphan*/  vtnrx_intrtask; int /*<<< orphan*/ * vtnrx_sg; struct vtnet_softc* vtnrx_sc; int /*<<< orphan*/  vtnrx_mtx; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_NOWAIT ; 
 int /*<<< orphan*/  TASK_INIT (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct vtnet_rxq*) ; 
 char* device_get_nameunit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sglist_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char*,int) ; 
 int /*<<< orphan*/ * taskqueue_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  taskqueue_thread_enqueue ; 
 int /*<<< orphan*/  vtnet_rxq_tq_intr ; 

__attribute__((used)) static int
vtnet_init_rxq(struct vtnet_softc *sc, int id)
{
	struct vtnet_rxq *rxq;

	rxq = &sc->vtnet_rxqs[id];

	snprintf(rxq->vtnrx_name, sizeof(rxq->vtnrx_name), "%s-rx%d",
	    device_get_nameunit(sc->vtnet_dev), id);
	mtx_init(&rxq->vtnrx_mtx, rxq->vtnrx_name, NULL, MTX_DEF);

	rxq->vtnrx_sc = sc;
	rxq->vtnrx_id = id;

	rxq->vtnrx_sg = sglist_alloc(sc->vtnet_rx_nsegs, M_NOWAIT);
	if (rxq->vtnrx_sg == NULL)
		return (ENOMEM);

	TASK_INIT(&rxq->vtnrx_intrtask, 0, vtnet_rxq_tq_intr, rxq);
	rxq->vtnrx_tq = taskqueue_create(rxq->vtnrx_name, M_NOWAIT,
	    taskqueue_thread_enqueue, &rxq->vtnrx_tq);

	return (rxq->vtnrx_tq == NULL ? ENOMEM : 0);
}