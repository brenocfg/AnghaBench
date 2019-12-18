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
struct g_mirror_softc {struct g_mirror_disk* sc_hint; int /*<<< orphan*/  sc_lock; } ;
struct g_mirror_disk {int d_state; int /*<<< orphan*/  d_consumer; struct g_mirror_softc* d_softc; } ;

/* Variables and functions */
#define  G_MIRROR_DISK_STATE_ACTIVE 131 
#define  G_MIRROR_DISK_STATE_NEW 130 
#define  G_MIRROR_DISK_STATE_STALE 129 
#define  G_MIRROR_DISK_STATE_SYNCHRONIZING 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct g_mirror_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_MIRROR ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  d_next ; 
 int /*<<< orphan*/  free (struct g_mirror_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mirror_disconnect_consumer (struct g_mirror_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mirror_disk_state2str (int) ; 
 int /*<<< orphan*/  g_mirror_event_cancel (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_mirror_get_diskname (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_mirror_sync_stop (struct g_mirror_disk*,int) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_mirror_destroy_disk(struct g_mirror_disk *disk)
{
	struct g_mirror_softc *sc;

	g_topology_assert_not();
	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_XLOCKED);

	g_topology_lock();
	LIST_REMOVE(disk, d_next);
	g_topology_unlock();
	g_mirror_event_cancel(disk);
	if (sc->sc_hint == disk)
		sc->sc_hint = NULL;
	switch (disk->d_state) {
	case G_MIRROR_DISK_STATE_SYNCHRONIZING:
		g_mirror_sync_stop(disk, 1);
		/* FALLTHROUGH */
	case G_MIRROR_DISK_STATE_NEW:
	case G_MIRROR_DISK_STATE_STALE:
	case G_MIRROR_DISK_STATE_ACTIVE:
		g_topology_lock();
		g_mirror_disconnect_consumer(sc, disk->d_consumer);
		g_topology_unlock();
		free(disk, M_MIRROR);
		break;
	default:
		KASSERT(0 == 1, ("Wrong disk state (%s, %s).",
		    g_mirror_get_diskname(disk),
		    g_mirror_disk_state2str(disk->d_state)));
	}
}