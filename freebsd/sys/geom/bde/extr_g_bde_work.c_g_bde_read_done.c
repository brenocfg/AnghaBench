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
struct g_bde_softc {int /*<<< orphan*/  worklist_mutex; } ;
struct g_bde_sector {scalar_t__ size; scalar_t__ error; int /*<<< orphan*/  state; } ;
struct bio {scalar_t__ bio_error; scalar_t__ bio_completed; struct g_bde_softc* bio_caller2; struct g_bde_sector* bio_caller1; } ;

/* Variables and functions */
 scalar_t__ EIO ; 
 int /*<<< orphan*/  G_T_TOPOLOGY ; 
 int /*<<< orphan*/  JUNK ; 
 int /*<<< orphan*/  VALID ; 
 int /*<<< orphan*/  g_destroy_bio (struct bio*) ; 
 int /*<<< orphan*/  g_trace (int /*<<< orphan*/ ,char*,struct g_bde_sector*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_bde_softc*) ; 

__attribute__((used)) static void
g_bde_read_done(struct bio *bp)
{
	struct g_bde_sector *sp;
	struct g_bde_softc *sc;

	sp = bp->bio_caller1;
	g_trace(G_T_TOPOLOGY, "g_bde_read_done(%p)", sp);
	sc = bp->bio_caller2;
	mtx_lock(&sc->worklist_mutex);
	if (bp->bio_error == 0 && bp->bio_completed != sp->size)
		bp->bio_error = EIO;
	sp->error = bp->bio_error;
	if (sp->error == 0)
		sp->state = VALID;
	else
		sp->state = JUNK;
	wakeup(sc);
	g_destroy_bio(bp);
	mtx_unlock(&sc->worklist_mutex);
}