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
typedef  size_t u_int ;
struct g_raid3_softc {int sc_flags; size_t sc_ndisks; int /*<<< orphan*/  sc_name; struct g_raid3_disk* sc_disks; int /*<<< orphan*/  sc_last_write; scalar_t__ sc_idle; int /*<<< orphan*/  sc_lock; } ;
struct g_raid3_disk {scalar_t__ d_state; int /*<<< orphan*/  d_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID3_DEBUG (int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int G_RAID3_DEVICE_FLAG_NOFAILSYNC ; 
 int /*<<< orphan*/  G_RAID3_DISK_FLAG_DIRTY ; 
 scalar_t__ G_RAID3_DISK_STATE_ACTIVE ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  g_raid3_get_diskname (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_raid3_update_metadata (struct g_raid3_disk*) ; 
 int /*<<< orphan*/  g_topology_assert_not () ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_uptime ; 

__attribute__((used)) static void
g_raid3_unidle(struct g_raid3_softc *sc)
{
	struct g_raid3_disk *disk;
	u_int i;

	g_topology_assert_not();
	sx_assert(&sc->sc_lock, SX_XLOCKED);

	if ((sc->sc_flags & G_RAID3_DEVICE_FLAG_NOFAILSYNC) != 0)
		return;
	sc->sc_idle = 0;
	sc->sc_last_write = time_uptime;
	for (i = 0; i < sc->sc_ndisks; i++) {
		disk = &sc->sc_disks[i];
		if (disk->d_state != G_RAID3_DISK_STATE_ACTIVE)
			continue;
		G_RAID3_DEBUG(1, "Disk %s (device %s) marked as dirty.",
		    g_raid3_get_diskname(disk), sc->sc_name);
		disk->d_flags |= G_RAID3_DISK_FLAG_DIRTY;
		g_raid3_update_metadata(disk);
	}
}