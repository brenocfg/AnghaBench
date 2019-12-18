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
struct g_rr_softc {int /*<<< orphan*/ * sc_active; struct g_geom* sc_geom; } ;
struct g_geom {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wait_miss; int /*<<< orphan*/  wait_hit; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_rr_queue_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_sched_dispatch (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_lock (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_unlock (struct g_geom*) ; 
 TYPE_1__ me ; 

__attribute__((used)) static void
g_rr_wait_timeout(void *data)
{
	struct g_rr_softc *sc = data;
	struct g_geom *geom = sc->sc_geom;

	g_sched_lock(geom);
	/*
	 * We can race with other events, so check if
	 * sc_active is still valid.
	 */
	if (sc->sc_active != NULL) {
		/* Release the reference to the queue. */
		g_rr_queue_put(sc->sc_active);
		sc->sc_active = NULL;
		me.wait_hit--;
		me.wait_miss++;	/* record the miss */
	}
	g_sched_dispatch(geom);
	g_sched_unlock(geom);
}