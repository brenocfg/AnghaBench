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
struct g_bde_work {scalar_t__ error; struct g_bde_sector* ksp; struct g_bde_sector* sp; TYPE_1__* bp; } ;
struct g_bde_softc {int /*<<< orphan*/  worklist_mutex; } ;
struct g_bde_sector {scalar_t__ size; scalar_t__ error; scalar_t__ state; struct g_bde_work* owner; } ;
struct bio {scalar_t__ bio_error; scalar_t__ bio_completed; struct g_bde_softc* bio_caller2; struct g_bde_sector* bio_caller1; } ;
struct TYPE_2__ {scalar_t__ bio_cmd; } ;

/* Variables and functions */
 scalar_t__ BIO_DELETE ; 
 scalar_t__ BIO_WRITE ; 
 scalar_t__ EIO ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ VALID ; 
 int /*<<< orphan*/  g_bde_delete_sector (struct g_bde_softc*,struct g_bde_sector*) ; 
 int /*<<< orphan*/  g_bde_work_done (struct g_bde_work*,scalar_t__) ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_bde_sector*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_bde_write_done(struct bio *bp)
{
	struct g_bde_sector *sp;
	struct g_bde_work *wp;
	struct g_bde_softc *sc;

	sp = bp->bio_caller1;
	sc = bp->bio_caller2;
	mtx_lock(&sc->worklist_mutex);
	KASSERT(sp != NULL, ("NULL sp"));
	KASSERT(sc != NULL, ("NULL sc"));
	KASSERT(sp->owner != NULL, ("NULL sp->owner"));
	g_trace(G_T_TOPOLOGY, "g_bde_write_done(%p)", sp);
	if (bp->bio_error == 0 && bp->bio_completed != sp->size)
		bp->bio_error = EIO;
	sp->error = bp->bio_error;
	g_destroy_bio(bp);
	wp = sp->owner;
	if (wp->error == 0)
		wp->error = sp->error;

	if (wp->bp->bio_cmd == BIO_DELETE) {
		KASSERT(sp == wp->sp, ("trashed delete op"));
		g_bde_work_done(wp, wp->error);
		mtx_unlock(&sc->worklist_mutex);
		return;
	}

	KASSERT(wp->bp->bio_cmd == BIO_WRITE, ("Confused in g_bde_write_done()"));
	KASSERT(sp == wp->sp || sp == wp->ksp, ("trashed write op"));
	if (wp->sp == sp) {
		g_bde_delete_sector(sc, wp->sp);
		wp->sp = NULL;
	} else {
		sp->state = VALID;
	}
	if (wp->sp == NULL && wp->ksp != NULL && wp->ksp->state == VALID)
		g_bde_work_done(wp, wp->error);
	mtx_unlock(&sc->worklist_mutex);
	return;
}