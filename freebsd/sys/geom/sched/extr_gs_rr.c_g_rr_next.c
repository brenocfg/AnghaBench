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
struct g_rr_softc {scalar_t__ sc_in_flight; struct g_rr_queue* sc_active; int /*<<< orphan*/  sc_rr_tailq; } ;
struct g_rr_queue {scalar_t__ q_status; int /*<<< orphan*/  q_bioq; scalar_t__ q_service; int /*<<< orphan*/  q_flags; } ;
struct bio {scalar_t__ bio_length; } ;
struct TYPE_2__ {scalar_t__ bypass; int /*<<< orphan*/  queue_depth; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_FLAG_COMPLETED ; 
 scalar_t__ G_QUEUE_BUSY ; 
 scalar_t__ G_QUEUE_READY ; 
 struct g_rr_queue* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct g_rr_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_rr_queue*,int /*<<< orphan*/ ) ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int g_rr_queue_expired (struct g_rr_queue*) ; 
 int /*<<< orphan*/  g_rr_queue_put (struct g_rr_queue*) ; 
 scalar_t__ g_rr_should_anticipate (struct g_rr_queue*,struct bio*) ; 
 scalar_t__ get_bounded (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__ me ; 
 int /*<<< orphan*/  q_tailq ; 

__attribute__((used)) static struct bio *
g_rr_next(void *data, int force)
{
	struct g_rr_softc *sc = data;
	struct g_rr_queue *qp;
	struct bio *bp, *next;
	int expired;

	qp = sc->sc_active;
	if (me.bypass == 0 && !force) {
		if (sc->sc_in_flight >= get_bounded(&me.queue_depth, 0))
			return (NULL);

		/* Try with the queue under service first. */
		if (qp != NULL && qp->q_status != G_QUEUE_READY) {
			/*
			 * Queue is anticipating, ignore request.
			 * We should check that we are not past
			 * the timeout, but in that case the timeout
			 * will fire immediately afterwards so we
			 * don't bother.
			 */
			return (NULL);
		}
	} else if (qp != NULL && qp->q_status != G_QUEUE_READY) {
		g_rr_queue_put(qp);
		sc->sc_active = qp = NULL;
	}

	/*
	 * No queue under service, look for the first in RR order.
	 * If we find it, select if as sc_active, clear service
	 * and record the end time of the slice.
	 */
	if (qp == NULL) {
		qp = TAILQ_FIRST(&sc->sc_rr_tailq);
		if (qp == NULL)
			return (NULL); /* no queues at all, return */
		/* otherwise select the new queue for service. */
		TAILQ_REMOVE(&sc->sc_rr_tailq, qp, q_tailq);
		sc->sc_active = qp;
		qp->q_service = 0;
		qp->q_flags &= ~G_FLAG_COMPLETED;
	}

	bp = bioq_takefirst(&qp->q_bioq);	/* surely not NULL */
	qp->q_service += bp->bio_length;	/* charge the service */

	/*
	 * The request at the head of the active queue is always
	 * dispatched, and gs_rr_next() will be called again
	 * immediately.
	 * We need to prepare for what to do next:
	 *
	 * 1. have we reached the end of the (time or service) slice ?
	 *    If so, clear sc_active and possibly requeue the previous
	 *    active queue if it has more requests pending;
	 * 2. do we have more requests in sc_active ?
	 *    If yes, do not anticipate, as gs_rr_next() will run again;
	 *    if no, decide whether or not to anticipate depending
	 *    on read or writes (e.g., anticipate only on reads).
	 */
	expired = g_rr_queue_expired(qp);	/* are we expired ? */
	next = bioq_first(&qp->q_bioq);	/* do we have one more ? */
 	if (expired) {
		sc->sc_active = NULL;
		/* Either requeue or release reference. */
		if (next != NULL)
			TAILQ_INSERT_TAIL(&sc->sc_rr_tailq, qp, q_tailq);
		else
			g_rr_queue_put(qp);
	} else if (next != NULL) {
		qp->q_status = G_QUEUE_READY;
	} else {
		if (!force && g_rr_should_anticipate(qp, bp)) {
			/* anticipate */
			qp->q_status = G_QUEUE_BUSY;
		} else {
			/* do not anticipate, release reference */
			g_rr_queue_put(qp);
			sc->sc_active = NULL;
		}
	}
	/* If sc_active != NULL, its q_status is always correct. */

	sc->sc_in_flight++;

	return (bp);
}