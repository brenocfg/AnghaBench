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
struct g_mountver_softc {int /*<<< orphan*/  sc_mtx; int /*<<< orphan*/  sc_queue; } ;
struct g_geom {struct g_mountver_softc* softc; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  G_MOUNTVER_LOGREQ (struct bio*,char*) ; 
 struct bio* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_queue ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_mountver_discard_queued(struct g_geom *gp)
{
	struct g_mountver_softc *sc;
	struct bio *bp;

	sc = gp->softc;

	mtx_lock(&sc->sc_mtx);
	while ((bp = TAILQ_FIRST(&sc->sc_queue)) != NULL) {
		TAILQ_REMOVE(&sc->sc_queue, bp, bio_queue);
		G_MOUNTVER_LOGREQ(bp, "Discarding queued request.");
		g_io_deliver(bp, ENXIO);
	}
	mtx_unlock(&sc->sc_mtx);
}