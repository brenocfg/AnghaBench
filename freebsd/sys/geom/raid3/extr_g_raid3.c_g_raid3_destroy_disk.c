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
struct g_raid3_softc {int /*<<< orphan*/ * sc_syncdisk; int /*<<< orphan*/  sc_lock; } ;
struct g_raid3_disk {int d_state; int /*<<< orphan*/ * d_consumer; struct g_raid3_softc* d_softc; } ;

/* Variables and functions */
#define  G_RAID3_DISK_STATE_ACTIVE 131 
#define  G_RAID3_DISK_STATE_NEW 130 
 int G_RAID3_DISK_STATE_NODISK ; 
#define  G_RAID3_DISK_STATE_STALE 129 
#define  G_RAID3_DISK_STATE_SYNCHRONIZING 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  g_raid3_disconnect_consumer (struct g_raid3_softc*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_raid3_disk_state2str (int) ; 
 int /*<<< orphan*/  g_raid3_event_cancel (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_sync_stop (struct g_raid3_softc*,int) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid3_destroy_disk(struct g_raid3_disk *disk)
{
	struct g_raid3_softc *sc;

	g_topology_assert_not();
	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_XLOCKED);

	if (disk->d_state == G_RAID3_DISK_STATE_NODISK)
		return;
	g_raid3_event_cancel(disk);
	switch (disk->d_state) {
	case G_RAID3_DISK_STATE_SYNCHRONIZING:
		if (sc->sc_syncdisk != NULL)
			g_raid3_sync_stop(sc, 1);
		/* FALLTHROUGH */
	case G_RAID3_DISK_STATE_NEW:
	case G_RAID3_DISK_STATE_STALE:
	case G_RAID3_DISK_STATE_ACTIVE:
		g_topology_lock();
		g_raid3_disconnect_consumer(sc, disk->d_consumer);
		g_topology_unlock();
		disk->d_consumer = NULL;
		break;
	default:
		KASSERT(0 == 1, ("Wrong disk state (%s, %s).",
		    g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
	}
	disk->d_state = G_RAID3_DISK_STATE_NODISK;
}