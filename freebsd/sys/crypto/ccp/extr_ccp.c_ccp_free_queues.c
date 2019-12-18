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
struct ccp_queue {int /*<<< orphan*/  cq_sg_dst; int /*<<< orphan*/  cq_sg_ulptx; int /*<<< orphan*/  cq_sg_crp; int /*<<< orphan*/  cq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  mtx_destroy (int /*<<< orphan*/ *) ; 
 size_t nitems (struct ccp_queue*) ; 
 int /*<<< orphan*/  sglist_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ccp_free_queues(struct ccp_softc *sc)
{
	struct ccp_queue *qp;
	size_t i;

	for (i = 0; i < nitems(sc->queues); i++) {
		qp = &sc->queues[i];

		mtx_destroy(&qp->cq_lock);
		sglist_free(qp->cq_sg_crp);
		sglist_free(qp->cq_sg_ulptx);
		sglist_free(qp->cq_sg_dst);
	}
}