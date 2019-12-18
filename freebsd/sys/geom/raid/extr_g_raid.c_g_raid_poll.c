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
struct g_raid_softc {scalar_t__ sc_geom; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_queue; int /*<<< orphan*/  sc_events; } ;
struct g_raid_event {int dummy; } ;
struct bio {TYPE_1__* bio_from; } ;
struct TYPE_2__ {scalar_t__ geom; } ;

/* Variables and functions */
 struct g_raid_event* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (int /*<<< orphan*/ *,struct g_raid_event*,int /*<<< orphan*/ ) ; 
 struct bio* bioq_takefirst (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  e_next ; 
 int /*<<< orphan*/  g_raid_disk_done_request (struct bio*) ; 
 int /*<<< orphan*/  g_raid_handle_event (struct g_raid_softc*,struct g_raid_event*) ; 
 int /*<<< orphan*/  g_raid_start_request (struct bio*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid_poll(struct g_raid_softc *sc)
{
	struct g_raid_event *ep;
	struct bio *bp;

	sx_xlock(&sc->sc_lock);
	mtx_lock(&sc->sc_queue_mtx);
	/*
	 * First take a look at events.
	 * This is important to handle events before any I/O requests.
	 */
	ep = TAILQ_FIRST(&sc->sc_events);
	if (ep != NULL) {
		TAILQ_REMOVE(&sc->sc_events, ep, e_next);
		mtx_unlock(&sc->sc_queue_mtx);
		g_raid_handle_event(sc, ep);
		goto out;
	}
	bp = bioq_takefirst(&sc->sc_queue);
	if (bp != NULL) {
		mtx_unlock(&sc->sc_queue_mtx);
		if (bp->bio_from == NULL ||
		    bp->bio_from->geom != sc->sc_geom)
			g_raid_start_request(bp);
		else
			g_raid_disk_done_request(bp);
	}
out:
	sx_xunlock(&sc->sc_lock);
}