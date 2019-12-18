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
struct g_raid3_softc {int sc_flags; int /*<<< orphan*/  sc_name; scalar_t__ sc_idle; int /*<<< orphan*/  sc_lock; } ;
struct g_raid3_disk {int d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int G_RAID3_DEVICE_FLAG_NOFAILSYNC ; 
 int G_RAID3_DISK_FLAG_DIRTY ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid3_update_idle(struct g_raid3_softc *sc, struct g_raid3_disk *disk)
{

	sx_assert(&sc->sc_lock, SX_LOCKED);
	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_NOFAILSYNC) != 0)
		return;
	if (!sc->sc_idle && (disk->d_flags & G_RAID3_DISK_FLAG_DIRTY) == 0) {
		G_RAID3_DEBUG(1, "Disk %s (device %s) marked as dirty.",
		    g_raid3_get_diskname(disk), sc->sc_name);
		disk->d_flags |= G_RAID3_DISK_FLAG_DIRTY;
	} else if (sc->sc_idle &&
	    (disk->d_flags & G_RAID3_DISK_FLAG_DIRTY) != 0) {
		G_RAID3_DEBUG(1, "Disk %s (device %s) marked as clean.",
		    g_raid3_get_diskname(disk), sc->sc_name);
		disk->d_flags &= ~G_RAID3_DISK_FLAG_DIRTY;
	}
}