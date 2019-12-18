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
struct g_sched_softc {int /*<<< orphan*/  sc_pending; int /*<<< orphan*/  sc_data; TYPE_1__* sc_gsched; } ;
struct g_geom {struct g_sched_softc* softc; } ;
struct bio {int /*<<< orphan*/  bio_caller1; struct g_geom* bio_caller2; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* gs_done ) (int /*<<< orphan*/ ,struct bio*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  DONE ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  TRC_BIO_EVENT (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  g_sched_flush_classes (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_lock (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_unlock (struct g_geom*) ; 
 int /*<<< orphan*/  g_sched_update_stats (struct bio*) ; 
 int /*<<< orphan*/  g_std_done (struct bio*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  wakeup (struct g_geom*) ; 

__attribute__((used)) static void
g_sched_done(struct bio *bio)
{
	struct g_geom *gp = bio->bio_caller2;
	struct g_sched_softc *sc = gp->softc;

	TRC_BIO_EVENT(DONE, bio);

	KASSERT(bio->bio_caller1, ("null bio_caller1 in g_sched_done"));

	g_sched_lock(gp);

	g_sched_update_stats(bio);
	sc->sc_gsched->gs_done(sc->sc_data, bio);
	if (!--sc->sc_pending)
		wakeup(gp);

	g_sched_flush_classes(gp);
	g_sched_unlock(gp);

	g_std_done(bio);
}