#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_raid3_softc {int /*<<< orphan*/ * sc_syncdisk; TYPE_1__* sc_provider; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_queue_mtx; int /*<<< orphan*/  sc_queue; } ;
struct bio {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  G_RAID3_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 struct bio* bioq_first (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bioq_remove (int /*<<< orphan*/ *,struct bio*) ; 
 int /*<<< orphan*/  g_error_provider (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_io_deliver (struct bio*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_sync_stop (struct g_raid3_softc*,int) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  g_wither_provider (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid3_destroy_provider(struct g_raid3_softc *sc)
{
	struct bio *bp;

	g_topology_assert_not();
	KASSERT(sc->sc_provider != NULL, ("NULL provider (device=%s).",
	    sc->sc_name));

	g_topology_lock();
	g_error_provider(sc->sc_provider, ENXIO);
	mtx_lock(&sc->sc_queue_mtx);
	while ((bp = bioq_first(&sc->sc_queue)) != NULL) {
		bioq_remove(&sc->sc_queue, bp);
		g_io_deliver(bp, ENXIO);
	}
	mtx_unlock(&sc->sc_queue_mtx);
	G_RAID3_DEBUG(0, "Device %s: provider %s destroyed.", sc->sc_name,
	    sc->sc_provider->name);
	g_wither_provider(sc->sc_provider, ENXIO);
	g_topology_unlock();
	sc->sc_provider = NULL;
	if (sc->sc_syncdisk != NULL)
		g_raid3_sync_stop(sc, 1);
}