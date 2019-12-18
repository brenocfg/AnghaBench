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
struct g_mountver_softc {scalar_t__ sc_orphaned; scalar_t__ sc_shutting_down; int /*<<< orphan*/  sc_queue; } ;
struct g_geom {struct g_mountver_softc* softc; } ;
struct bio {TYPE_1__* bio_to; } ;
struct TYPE_2__ {struct g_geom* geom; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  G_MOUNTVER_LOGREQ (struct bio*,char*) ; 
 int /*<<< orphan*/  TAILQ_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mountver_queue (struct bio*) ; 
 int /*<<< orphan*/  g_mountver_send (struct bio*) ; 
 int /*<<< orphan*/  g_mountver_send_queued (struct g_geom*) ; 

__attribute__((used)) static void
g_mountver_start(struct bio *bp)
{
	struct g_mountver_softc *sc;
	struct g_geom *gp;

	gp = bp->bio_to->geom;
	sc = gp->softc;
	G_MOUNTVER_LOGREQ(bp, "Request received.");

	/*
	 * It is possible that some bios were returned with ENXIO, even though
	 * orphaning didn't happen yet.  In that case, queue all subsequent
	 * requests in order to maintain ordering.
	 */
	if (sc->sc_orphaned || !TAILQ_EMPTY(&sc->sc_queue)) {
		if (sc->sc_shutting_down) {
			G_MOUNTVER_LOGREQ(bp, "Discarding request due to shutdown.");
			g_io_deliver(bp, ENXIO);
			return;
		}
		G_MOUNTVER_LOGREQ(bp, "Queueing request.");
		g_mountver_queue(bp);
		if (!sc->sc_orphaned)
			g_mountver_send_queued(gp);
	} else {
		G_MOUNTVER_LOGREQ(bp, "Sending request.");
		g_mountver_send(bp);
	}
}