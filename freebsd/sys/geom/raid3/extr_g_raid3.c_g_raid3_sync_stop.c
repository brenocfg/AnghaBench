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
struct g_raid3_softc {scalar_t__ sc_state; int /*<<< orphan*/  sc_lock; int /*<<< orphan*/  sc_name; struct g_raid3_disk* sc_syncdisk; } ;
struct TYPE_2__ {struct g_consumer* ds_consumer; int /*<<< orphan*/ * ds_bios; } ;
struct g_raid3_disk {scalar_t__ d_state; int /*<<< orphan*/  d_flags; TYPE_1__ d_sync; } ;
struct g_consumer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ G_RAID3_DEVICE_STATE_DEGRADED ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_DIRTY ; 
 scalar_t__ G_RAID3_DISK_STATE_SYNCHRONIZING ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  M_RAID3 ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_disk_state2str (scalar_t__) ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_kill_consumer (struct g_raid3_softc*,struct g_consumer*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  g_topology_lock () ; 
 int /*<<< orphan*/  g_topology_unlock () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_xlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_xunlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
g_raid3_sync_stop(struct g_raid3_softc *sc, int type)
{
	struct g_raid3_disk *disk;
	struct g_consumer *cp;

	g_topology_assert_not();
	sx_assert(&sc->sc_lock, SX_LOCKED);

	KASSERT(sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED,
	    ("Device not in DEGRADED state (%s, %u).", sc->sc_name,
	    sc->sc_state));
	disk = sc->sc_syncdisk;
	sc->sc_syncdisk = NULL;
	KASSERT(disk != NULL, ("No disk was synchronized (%s).", sc->sc_name));
	KASSERT(disk->d_state == G_RAID3_DISK_STATE_SYNCHRONIZING,
	    ("Wrong disk state (%s, %s).", g_raid3_get_diskname(disk),
	    g_raid3_disk_state2str(disk->d_state)));
	if (disk->d_sync.ds_consumer == NULL)
		return;

	if (type == 0) {
		G_RAID3_DEBUG(0, "Device %s: rebuilding provider %s finished.",
		    sc->sc_name, g_raid3_get_diskname(disk));
	} else /* if (type == 1) */ {
		G_RAID3_DEBUG(0, "Device %s: rebuilding provider %s stopped.",
		    sc->sc_name, g_raid3_get_diskname(disk));
	}
	free(disk->d_sync.ds_bios, M_RAID3);
	disk->d_sync.ds_bios = NULL;
	cp = disk->d_sync.ds_consumer;
	disk->d_sync.ds_consumer = NULL;
	disk->d_flags &= ~G_RAID3_DISK_FLAG_DIRTY;
	sx_xunlock(&sc->sc_lock); /* Avoid recursion on sc_lock. */
	g_topology_lock();
	g_raid3_kill_consumer(sc, cp);
	g_topology_unlock();
	sx_xlock(&sc->sc_lock);
}