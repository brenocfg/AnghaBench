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
struct ccp_softc {struct ccp_queue* queues; } ;
struct ccp_queue {size_t cq_qindex; void* cq_sg_dst; void* cq_sg_ulptx; void* cq_sg_crp; int /*<<< orphan*/  cq_lock; struct ccp_softc* cq_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  MTX_DEF ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int /*<<< orphan*/  mtx_init (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 size_t nitems (struct ccp_queue*) ; 
 void* sglist_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccp_initialize_queues(struct ccp_softc *sc)
{
	struct ccp_queue *qp;
	size_t i;

	for (i = 0; i < nitems(sc->queues); i++) {
		qp = &sc->queues[i];

		qp->cq_softc = sc;
		qp->cq_qindex = i;
		mtx_init(&qp->cq_lock, "ccp queue", NULL, MTX_DEF);
		/* XXX - arbitrarily chosen sizes */
		qp->cq_sg_crp = sglist_alloc(32, M_WAITOK);
		/* Two more SGEs than sg_crp to accommodate ipad. */
		qp->cq_sg_ulptx = sglist_alloc(34, M_WAITOK);
		qp->cq_sg_dst = sglist_alloc(2, M_WAITOK);
	}
}