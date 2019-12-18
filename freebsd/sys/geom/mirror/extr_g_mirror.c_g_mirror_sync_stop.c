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
struct TYPE_4__ {int /*<<< orphan*/  ds_ndisks; } ;
struct g_mirror_softc {int /*<<< orphan*/  sc_lock; TYPE_2__ sc_sync; int /*<<< orphan*/  sc_name; } ;
struct TYPE_3__ {struct g_consumer* ds_consumer; int /*<<< orphan*/ * ds_bios; } ;
struct g_mirror_disk {scalar_t__ d_state; int /*<<< orphan*/  d_flags; TYPE_1__ d_sync; struct g_mirror_softc* d_softc; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  G_MIRROR_DISK_FLAG_DIRTY ; 
 scalar_t__ G_MIRROR_DISK_STATE_SYNCHRONIZING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_MIRROR ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mirror_disk_state2str (scalar_t__) ; 
 int /*<<< orphan*/  g_mirror_get_diskname (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_mirror_kill_consumer (struct g_mirror_softc*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_mirror_regular_release (struct g_mirror_softc*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_mirror_sync_stop(struct g_mirror_disk *disk, int type)
{
	struct g_mirror_softc *sc;
	struct g_consumer *cp;

	g_topology_assert_not();
	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_LOCKED);

	KASSERT(disk->d_state == G_MIRROR_DISK_STATE_SYNCHRONIZING,
	    ("Wrong disk state (%s, %s).", g_mirror_get_diskname(disk),
	    g_mirror_disk_state2str(disk->d_state)));
	if (disk->d_sync.ds_consumer == NULL)
		return;

	if (type == 0) {
		G_MIRROR_DEBUG(0, "Device %s: rebuilding provider %s finished.",
		    sc->sc_name, g_mirror_get_diskname(disk));
	} else /* if (type == 1) */ {
		G_MIRROR_DEBUG(0, "Device %s: rebuilding provider %s stopped.",
		    sc->sc_name, g_mirror_get_diskname(disk));
	}
	g_mirror_regular_release(sc);
	free(disk->d_sync.ds_bios, M_MIRROR);
	disk->d_sync.ds_bios = NULL;
	cp = disk->d_sync.ds_consumer;
	disk->d_sync.ds_consumer = NULL;
	disk->d_flags &= ~G_MIRROR_DISK_FLAG_DIRTY;
	sc->sc_sync.ds_ndisks--;
	sx_xunlock(&sc->sc_lock); /* Avoid recursion on sc_lock. */
	g_topology_lock();
	g_mirror_kill_consumer(sc, cp);
	g_topology_unlock();
	sx_xlock(&sc->sc_lock);
}