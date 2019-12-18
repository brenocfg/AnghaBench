#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct g_sched_softc {int sc_flags; int /*<<< orphan*/  sc_pending; int /*<<< orphan*/  sc_data; TYPE_1__* sc_gsched; } ;
struct g_geom {int /*<<< orphan*/  consumer; int /*<<< orphan*/  provider; struct g_sched_softc* softc; } ;
struct bio {scalar_t__ bio_cmd; TYPE_2__* bio_caller1; int /*<<< orphan*/  bio_done; scalar_t__ bio_length; struct g_geom* bio_caller2; TYPE_3__* bio_to; } ;
struct TYPE_7__ {struct g_geom* geom; } ;
struct TYPE_6__ {int /*<<< orphan*/  gs_write_bytes_in_flight; int /*<<< orphan*/  gs_writes_in_flight; int /*<<< orphan*/  gs_bytes_in_flight; int /*<<< orphan*/  gs_requests; int /*<<< orphan*/  gs_in_flight; } ;
struct TYPE_5__ {scalar_t__ (* gs_start ) (int /*<<< orphan*/ ,struct bio*) ;} ;

/* Variables and functions */
 scalar_t__ BIO_READ ; 
 scalar_t__ BIO_WRITE ; 
 int /*<<< orphan*/  ENOMEM ; 
 int G_SCHED_FLUSHING ; 
 int /*<<< orphan*/  G_SCHED_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 TYPE_3__* LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  START ; 
 int /*<<< orphan*/  TRC_BIO_EVENT (int /*<<< orphan*/ ,struct bio*) ; 
 struct bio* g_clone_bio (struct bio*) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_request (struct bio*,TYPE_3__*) ; 
 int /*<<< orphan*/  g_sched_dispatch (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_done ; 
 int /*<<< orphan*/  g_sched_lock (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_unlock (struct g_geom*) ; 
 int /*<<< orphan*/  g_std_done ; 
 TYPE_2__ me ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,struct bio*) ; 

__attribute__((used)) static void
g_sched_start(struct bio *bp)
{
	struct g_geom *gp = bp->bio_to->geom;
	struct g_sched_softc *sc = gp->softc;
	struct bio *cbp;

	TRC_BIO_EVENT(START, bp);
	G_SCHED_LOGREQ(bp, "Request received.");

	cbp = g_clone_bio(bp);
	if (cbp == NULL) {
		g_io_deliver(bp, ENOMEM);
		return;
	}
	cbp->bio_done = g_sched_done;
	cbp->bio_to = LIST_FIRST(&gp->provider);
	KASSERT(cbp->bio_to != NULL, ("NULL provider"));

	/* We only schedule reads and writes. */
	if (bp->bio_cmd != BIO_READ && bp->bio_cmd != BIO_WRITE)
		goto bypass;

	G_SCHED_LOGREQ(cbp, "Sending request.");

	g_sched_lock(gp);
	/*
	 * Call the algorithm's gs_start to queue the request in the
	 * scheduler. If gs_start fails then pass the request down,
	 * otherwise call g_sched_dispatch() which tries to push
	 * one or more requests down.
	 */
	if (!sc->sc_gsched || (sc->sc_flags & G_SCHED_FLUSHING) ||
	    sc->sc_gsched->gs_start(sc->sc_data, cbp)) {
		g_sched_unlock(gp);
		goto bypass;
	}
	/*
	 * We use bio_caller1 to mark requests that are scheduled
	 * so make sure it is not NULL.
	 */
	if (cbp->bio_caller1 == NULL)
		cbp->bio_caller1 = &me;	/* anything not NULL */

	cbp->bio_caller2 = gp;
	sc->sc_pending++;

	/* Update general stats. */
	me.gs_in_flight++;
	me.gs_requests++;
	me.gs_bytes_in_flight += bp->bio_length;
	if (bp->bio_cmd == BIO_WRITE) {
		me.gs_writes_in_flight++;
		me.gs_write_bytes_in_flight += bp->bio_length;
	}
	g_sched_dispatch(gp);
	g_sched_unlock(gp);
	return;

bypass:
	cbp->bio_done = g_std_done;
	cbp->bio_caller1 = NULL; /* not scheduled */
	g_io_request(cbp, LIST_FIRST(&gp->consumer));
}