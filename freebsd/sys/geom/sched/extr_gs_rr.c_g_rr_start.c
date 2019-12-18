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
struct g_rr_softc {int /*<<< orphan*/  sc_rr_tailq; int /*<<< orphan*/  sc_wait; struct g_rr_queue* sc_active; } ;
struct g_rr_queue {int q_bionum; int /*<<< orphan*/  q_bioq; int /*<<< orphan*/  q_status; } ;
struct bio {struct g_rr_queue* bio_caller1; } ;
struct TYPE_2__ {scalar_t__ bypass; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_QUEUE_READY ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct g_rr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/ * bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  callout_stop (int /*<<< orphan*/ *) ; 
 struct g_rr_queue* g_rr_queue_get (struct g_rr_softc*,struct bio*) ; 
 int /*<<< orphan*/  g_rr_update_seekdist (struct g_rr_queue*,struct bio*) ; 
 int /*<<< orphan*/  g_rr_update_thinktime (struct g_rr_queue*) ; 
 int /*<<< orphan*/  g_sched_priv_ref (struct g_rr_queue*) ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  q_tailq ; 

__attribute__((used)) static int
g_rr_start(void *data, struct bio *bp)
{
	struct g_rr_softc *sc = data;
	struct g_rr_queue *qp;

	if (me.bypass)
		return (-1);	/* bypass the scheduler */

	/* Get the queue for the request. */
	qp = g_rr_queue_get(sc, bp);
	if (qp == NULL)
		return (-1); /* allocation failed, tell upstream */

	if (bioq_first(&qp->q_bioq) == NULL) {
		/*
		 * We are inserting into an empty queue.
		 * Reset its state if it is sc_active,
		 * otherwise insert it in the RR list.
		 */
		if (qp == sc->sc_active) {
			qp->q_status = G_QUEUE_READY;
			callout_stop(&sc->sc_wait);
		} else {
			g_sched_priv_ref(qp);
			TAILQ_INSERT_TAIL(&sc->sc_rr_tailq, qp, q_tailq);
		}
	}

	qp->q_bionum = 1 + qp->q_bionum - (qp->q_bionum >> 3);

	g_rr_update_thinktime(qp);
	g_rr_update_seekdist(qp, bp);

	/* Inherit the reference returned by g_rr_queue_get(). */
	bp->bio_caller1 = qp;
	bioq_disksort(&qp->q_bioq, bp);

	return (0);
}