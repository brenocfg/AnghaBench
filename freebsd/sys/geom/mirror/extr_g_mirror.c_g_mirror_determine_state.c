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
typedef  int /*<<< orphan*/  u_int ;
struct g_mirror_softc {scalar_t__ sc_syncid; int sc_flags; int /*<<< orphan*/  sc_name; } ;
struct TYPE_2__ {scalar_t__ ds_syncid; scalar_t__ ds_offset_done; scalar_t__ ds_offset; } ;
struct g_mirror_disk {int d_flags; TYPE_1__ d_sync; struct g_mirror_softc* d_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_MIRROR_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int G_MIRROR_DEVICE_FLAG_NOAUTOSYNC ; 
 int G_MIRROR_DISK_FLAG_DIRTY ; 
 int G_MIRROR_DISK_FLAG_FORCE_SYNC ; 
 int G_MIRROR_DISK_FLAG_SYNCHRONIZING ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_ACTIVE ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_NONE ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_STALE ; 
 int /*<<< orphan*/  G_MIRROR_DISK_STATE_SYNCHRONIZING ; 
 int /*<<< orphan*/  g_mirror_destroy_disk (struct g_mirror_disk*) ; 
 int /*<<< orphan*/  g_mirror_disk_state2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_mirror_get_diskname (struct g_mirror_disk*) ; 
 scalar_t__ g_mirror_ndisks (struct g_mirror_softc*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_int
g_mirror_determine_state(struct g_mirror_disk *disk)
{
	struct g_mirror_softc *sc;
	u_int state;

	sc = disk->d_softc;
	if (sc->sc_syncid == disk->d_sync.ds_syncid) {
		if ((disk->d_flags &
		    G_MIRROR_DISK_FLAG_SYNCHRONIZING) == 0 &&
		    (g_mirror_ndisks(sc, G_MIRROR_DISK_STATE_ACTIVE) == 0 ||
		     (disk->d_flags & G_MIRROR_DISK_FLAG_DIRTY) == 0)) {
			/* Disk does not need synchronization. */
			state = G_MIRROR_DISK_STATE_ACTIVE;
		} else {
			if ((sc->sc_flags &
			     G_MIRROR_DEVICE_FLAG_NOAUTOSYNC) == 0 ||
			    (disk->d_flags &
			     G_MIRROR_DISK_FLAG_FORCE_SYNC) != 0) {
				/*
				 * We can start synchronization from
				 * the stored offset.
				 */
				state = G_MIRROR_DISK_STATE_SYNCHRONIZING;
			} else {
				state = G_MIRROR_DISK_STATE_STALE;
			}
		}
	} else if (disk->d_sync.ds_syncid < sc->sc_syncid) {
		/*
		 * Reset all synchronization data for this disk,
		 * because if it even was synchronized, it was
		 * synchronized to disks with different syncid.
		 */
		disk->d_flags |= G_MIRROR_DISK_FLAG_SYNCHRONIZING;
		disk->d_sync.ds_offset = 0;
		disk->d_sync.ds_offset_done = 0;
		disk->d_sync.ds_syncid = sc->sc_syncid;
		if ((sc->sc_flags & G_MIRROR_DEVICE_FLAG_NOAUTOSYNC) == 0 ||
		    (disk->d_flags & G_MIRROR_DISK_FLAG_FORCE_SYNC) != 0) {
			state = G_MIRROR_DISK_STATE_SYNCHRONIZING;
		} else {
			state = G_MIRROR_DISK_STATE_STALE;
		}
	} else /* if (sc->sc_syncid < disk->d_sync.ds_syncid) */ {
		/*
		 * Not good, NOT GOOD!
		 * It means that mirror was started on stale disks
		 * and more fresh disk just arrive.
		 * If there were writes, mirror is broken, sorry.
		 * I think the best choice here is don't touch
		 * this disk and inform the user loudly.
		 */
		G_MIRROR_DEBUG(0, "Device %s was started before the freshest "
		    "disk (%s) arrives!! It will not be connected to the "
		    "running device.", sc->sc_name,
		    g_mirror_get_diskname(disk));
		g_mirror_destroy_disk(disk);
		state = G_MIRROR_DISK_STATE_NONE;
		/* Return immediately, because disk was destroyed. */
		return (state);
	}
	G_MIRROR_DEBUG(3, "State for %s disk: %s.",
	    g_mirror_get_diskname(disk), g_mirror_disk_state2str(state));
	return (state);
}