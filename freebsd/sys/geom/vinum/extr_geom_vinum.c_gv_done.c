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
struct gv_softc {int /*<<< orphan*/  bqueue_mtx; int /*<<< orphan*/  bqueue_up; } ;
struct g_geom {struct gv_softc* softc; } ;
struct bio {TYPE_1__* bio_from; } ;
struct TYPE_2__ {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct gv_softc*) ; 

void
gv_done(struct bio *bp)
{
	struct g_geom *gp;
	struct gv_softc *sc;
	
	KASSERT(bp != NULL, ("NULL bp"));

	gp = bp->bio_from->geom;
	sc = gp->softc;

	mtx_lock(&sc->bqueue_mtx);
	bioq_disksort(sc->bqueue_up, bp);
	wakeup(sc);
	mtx_unlock(&sc->bqueue_mtx);
}