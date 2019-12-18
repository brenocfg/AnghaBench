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
struct g_raid_subdisk {struct g_raid_softc* sd_softc; } ;
struct g_raid_softc {int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_queue; } ;
struct bio {struct g_raid_subdisk* bio_caller1; } ;

/* Variables and functions */
 int /*<<< orphan*/  bioq_insert_tail (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  dumping ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wakeup (struct g_raid_softc*) ; 

__attribute__((used)) static void
g_raid_disk_done(struct bio *bp)
{
	struct g_raid_softc *sc;
	struct g_raid_subdisk *sd;

	sd = bp->bio_caller1;
	sc = sd->sd_softc;
	mtx_lock(&sc->sc_queue_mtx);
	bioq_insert_tail(&sc->sc_queue, bp);
	mtx_unlock(&sc->sc_queue_mtx);
	if (!dumping)
		wakeup(sc);
}