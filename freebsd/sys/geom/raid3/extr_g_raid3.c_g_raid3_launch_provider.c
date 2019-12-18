#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_raid3_softc {int sc_ndisks; scalar_t__ sc_state; struct g_provider* sc_provider; struct g_raid3_disk* sc_disks; int /*<<< orphan*/  sc_sectorsize; int /*<<< orphan*/  sc_mediasize; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_geom; int /*<<< orphan*/  sc_lock; } ;
struct g_raid3_disk {TYPE_2__* d_consumer; } ;
struct g_provider {int stripesize; int stripeoffset; int /*<<< orphan*/  name; int /*<<< orphan*/  sectorsize; int /*<<< orphan*/  mediasize; } ;
struct TYPE_4__ {TYPE_1__* provider; } ;
struct TYPE_3__ {int stripesize; int stripeoffset; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ G_RAID3_DEVICE_STATE_DEGRADED ; 
 int /*<<< orphan*/  G_RAID3_DISK_STATE_ACTIVE ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  g_error_provider (struct g_provider*,int /*<<< orphan*/ ) ; 
 struct g_provider* g_new_providerf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_ndisks (struct g_raid3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_sync_start (struct g_raid3_softc*) ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid3_launch_provider(struct g_raid3_softc *sc)
{
	struct g_provider *pp;
	struct g_raid3_disk *disk;
	int n;

	sx_assert(&sc->sc_lock, SX_LOCKED);

	g_topology_lock();
	pp = g_new_providerf(sc->sc_geom, "raid3/%s", sc->sc_name);
	pp->mediasize = sc->sc_mediasize;
	pp->sectorsize = sc->sc_sectorsize;
	pp->stripesize = 0;
	pp->stripeoffset = 0;
	for (n = 0; n < sc->sc_ndisks; n++) {
		disk = &sc->sc_disks[n];
		if (disk->d_consumer && disk->d_consumer->provider &&
		    disk->d_consumer->provider->stripesize > pp->stripesize) {
			pp->stripesize = disk->d_consumer->provider->stripesize;
			pp->stripeoffset = disk->d_consumer->provider->stripeoffset;
		}
	}
	pp->stripesize *= sc->sc_ndisks - 1;
	pp->stripeoffset *= sc->sc_ndisks - 1;
	sc->sc_provider = pp;
	g_error_provider(pp, 0);
	g_topology_unlock();
	G_RAID3_DEBUG(0, "Device %s launched (%u/%u).", pp->name,
	    g_raid3_ndisks(sc, G_RAID3_DISK_STATE_ACTIVE), sc->sc_ndisks);

	if (sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED)
		g_raid3_sync_start(sc);
}