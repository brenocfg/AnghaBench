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
struct g_uzip_softc {int /*<<< orphan*/  queue_mtx; int /*<<< orphan*/  bio_queue; } ;
struct g_geom {struct g_uzip_softc* softc; } ;
struct bio {TYPE_1__* bio_to; struct bio* bio_parent; } ;
struct TYPE_2__ {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioq_disksort (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_uzip_softc*) ; 

__attribute__((used)) static void
g_uzip_read_done(struct bio *bp)
{
	struct bio *bp2;
	struct g_geom *gp;
	struct g_uzip_softc *sc;

	bp2 = bp->bio_parent;
	gp = bp2->bio_to->geom;
	sc = gp->softc;

	mtx_lock(&sc->queue_mtx);
	bioq_disksort(&sc->bio_queue, bp);
	mtx_unlock(&sc->queue_mtx);
	wakeup(sc);
}