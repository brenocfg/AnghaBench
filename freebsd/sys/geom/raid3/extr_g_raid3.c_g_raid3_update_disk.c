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
typedef  int u_int ;
struct g_raid3_softc {int sc_flags; int sc_bump_id; int /*<<< orphan*/  sc_name; int /*<<< orphan*/  sc_state; int /*<<< orphan*/ * sc_provider; int /*<<< orphan*/  sc_lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  ds_offset_done; int /*<<< orphan*/  ds_offset; } ;
struct g_raid3_disk {int d_state; int /*<<< orphan*/  d_flags; TYPE_1__ d_sync; struct g_raid3_softc* d_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_STATE_CHANGED () ; 
 int G_RAID3_BUMP_SYNCID ; 
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int G_RAID3_DEVICE_FLAG_NOAUTOSYNC ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_STATE_COMPLETE ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_STATE_DEGRADED ; 
 int /*<<< orphan*/  G_RAID3_DEVICE_STATE_STARTING ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_DIRTY ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_FORCE_SYNC ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_SYNCHRONIZING ; 
#define  G_RAID3_DISK_STATE_ACTIVE 132 
#define  G_RAID3_DISK_STATE_DISCONNECTED 131 
#define  G_RAID3_DISK_STATE_NEW 130 
 int G_RAID3_DISK_STATE_NONE ; 
#define  G_RAID3_DISK_STATE_STALE 129 
#define  G_RAID3_DISK_STATE_SYNCHRONIZING 128 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  g_raid3_destroy_disk (struct g_raid3_disk*) ; 
 int g_raid3_determine_state (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_device_state2str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_disk_state2str (int) ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_sync_start (struct g_raid3_softc*) ; 
 int /*<<< orphan*/  g_raid3_sync_stop (struct g_raid3_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid3_update_idle (struct g_raid3_softc*,struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_update_metadata (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
g_raid3_update_disk(struct g_raid3_disk *disk, u_int state)
{
	struct g_raid3_softc *sc;

	sc = disk->d_softc;
	sx_assert(&sc->sc_lock, SX_XLOCKED);

again:
	G_RAID3_DEBUG(3, "Changing disk %s state from %s to %s.",
	    g_raid3_get_diskname(disk), g_raid3_disk_state2str(disk->d_state),
	    g_raid3_disk_state2str(state));
	switch (state) {
	case G_RAID3_DISK_STATE_NEW:
		/*
		 * Possible scenarios:
		 * 1. New disk arrive.
		 */
		/* Previous state should be NONE. */
		KASSERT(disk->d_state == G_RAID3_DISK_STATE_NONE,
		    ("Wrong disk state (%s, %s).", g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		DISK_STATE_CHANGED();

		disk->d_state = state;
		G_RAID3_DEBUG(1, "Device %s: provider %s detected.",
		    sc->sc_name, g_raid3_get_diskname(disk));
		if (sc->sc_state == G_RAID3_DEVICE_STATE_STARTING)
			break;
		KASSERT(sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED ||
		    sc->sc_state == G_RAID3_DEVICE_STATE_COMPLETE,
		    ("Wrong device state (%s, %s, %s, %s).", sc->sc_name,
		    g_raid3_device_state2str(sc->sc_state),
		    g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		state = g_raid3_determine_state(disk);
		if (state != G_RAID3_DISK_STATE_NONE)
			goto again;
		break;
	case G_RAID3_DISK_STATE_ACTIVE:
		/*
		 * Possible scenarios:
		 * 1. New disk does not need synchronization.
		 * 2. Synchronization process finished successfully.
		 */
		KASSERT(sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED ||
		    sc->sc_state == G_RAID3_DEVICE_STATE_COMPLETE,
		    ("Wrong device state (%s, %s, %s, %s).", sc->sc_name,
		    g_raid3_device_state2str(sc->sc_state),
		    g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		/* Previous state should be NEW or SYNCHRONIZING. */
		KASSERT(disk->d_state == G_RAID3_DISK_STATE_NEW ||
		    disk->d_state == G_RAID3_DISK_STATE_SYNCHRONIZING,
		    ("Wrong disk state (%s, %s).", g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		DISK_STATE_CHANGED();

		if (disk->d_state == G_RAID3_DISK_STATE_SYNCHRONIZING) {
			disk->d_flags &= ~G_RAID3_DISK_FLAG_SYNCHRONIZING;
			disk->d_flags &= ~G_RAID3_DISK_FLAG_FORCE_SYNC;
			g_raid3_sync_stop(sc, 0);
		}
		disk->d_state = state;
		disk->d_sync.ds_offset = 0;
		disk->d_sync.ds_offset_done = 0;
		g_raid3_update_idle(sc, disk);
		g_raid3_update_metadata(disk);
		G_RAID3_DEBUG(1, "Device %s: provider %s activated.",
		    sc->sc_name, g_raid3_get_diskname(disk));
		break;
	case G_RAID3_DISK_STATE_STALE:
		/*
		 * Possible scenarios:
		 * 1. Stale disk was connected.
		 */
		/* Previous state should be NEW. */
		KASSERT(disk->d_state == G_RAID3_DISK_STATE_NEW,
		    ("Wrong disk state (%s, %s).", g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		KASSERT(sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED ||
		    sc->sc_state == G_RAID3_DEVICE_STATE_COMPLETE,
		    ("Wrong device state (%s, %s, %s, %s).", sc->sc_name,
		    g_raid3_device_state2str(sc->sc_state),
		    g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		/*
		 * STALE state is only possible if device is marked
		 * NOAUTOSYNC.
		 */
		KASSERT((sc->sc_flags & G_RAID3_DEVICE_FLAG_NOAUTOSYNC) != 0,
		    ("Wrong device state (%s, %s, %s, %s).", sc->sc_name,
		    g_raid3_device_state2str(sc->sc_state),
		    g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		DISK_STATE_CHANGED();

		disk->d_flags &= ~G_RAID3_DISK_FLAG_DIRTY;
		disk->d_state = state;
		g_raid3_update_metadata(disk);
		G_RAID3_DEBUG(0, "Device %s: provider %s is stale.",
		    sc->sc_name, g_raid3_get_diskname(disk));
		break;
	case G_RAID3_DISK_STATE_SYNCHRONIZING:
		/*
		 * Possible scenarios:
		 * 1. Disk which needs synchronization was connected.
		 */
		/* Previous state should be NEW. */
		KASSERT(disk->d_state == G_RAID3_DISK_STATE_NEW,
		    ("Wrong disk state (%s, %s).", g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		KASSERT(sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED ||
		    sc->sc_state == G_RAID3_DEVICE_STATE_COMPLETE,
		    ("Wrong device state (%s, %s, %s, %s).", sc->sc_name,
		    g_raid3_device_state2str(sc->sc_state),
		    g_raid3_get_diskname(disk),
		    g_raid3_disk_state2str(disk->d_state)));
		DISK_STATE_CHANGED();

		if (disk->d_state == G_RAID3_DISK_STATE_NEW)
			disk->d_flags &= ~G_RAID3_DISK_FLAG_DIRTY;
		disk->d_state = state;
		if (sc->sc_provider != NULL) {
			g_raid3_sync_start(sc);
			g_raid3_update_metadata(disk);
		}
		break;
	case G_RAID3_DISK_STATE_DISCONNECTED:
		/*
		 * Possible scenarios:
		 * 1. Device wasn't running yet, but disk disappear.
		 * 2. Disk was active and disapppear.
		 * 3. Disk disappear during synchronization process.
		 */
		if (sc->sc_state == G_RAID3_DEVICE_STATE_DEGRADED ||
		    sc->sc_state == G_RAID3_DEVICE_STATE_COMPLETE) {
			/*
			 * Previous state should be ACTIVE, STALE or
			 * SYNCHRONIZING.
			 */
			KASSERT(disk->d_state == G_RAID3_DISK_STATE_ACTIVE ||
			    disk->d_state == G_RAID3_DISK_STATE_STALE ||
			    disk->d_state == G_RAID3_DISK_STATE_SYNCHRONIZING,
			    ("Wrong disk state (%s, %s).",
			    g_raid3_get_diskname(disk),
			    g_raid3_disk_state2str(disk->d_state)));
		} else if (sc->sc_state == G_RAID3_DEVICE_STATE_STARTING) {
			/* Previous state should be NEW. */
			KASSERT(disk->d_state == G_RAID3_DISK_STATE_NEW,
			    ("Wrong disk state (%s, %s).",
			    g_raid3_get_diskname(disk),
			    g_raid3_disk_state2str(disk->d_state)));
			/*
			 * Reset bumping syncid if disk disappeared in STARTING
			 * state.
			 */
			if ((sc->sc_bump_id & G_RAID3_BUMP_SYNCID) != 0)
				sc->sc_bump_id &= ~G_RAID3_BUMP_SYNCID;
#ifdef	INVARIANTS
		} else {
			KASSERT(1 == 0, ("Wrong device state (%s, %s, %s, %s).",
			    sc->sc_name,
			    g_raid3_device_state2str(sc->sc_state),
			    g_raid3_get_diskname(disk),
			    g_raid3_disk_state2str(disk->d_state)));
#endif
		}
		DISK_STATE_CHANGED();
		G_RAID3_DEBUG(0, "Device %s: provider %s disconnected.",
		    sc->sc_name, g_raid3_get_diskname(disk));

		g_raid3_destroy_disk(disk);
		break;
	default:
		KASSERT(1 == 0, ("Unknown state (%u).", state));
		break;
	}
	return (0);
}