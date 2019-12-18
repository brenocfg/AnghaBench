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
typedef  int u_int ;
struct g_raid_softc {int dummy; } ;
struct g_raid_md_object {struct g_raid_softc* mdo_softc; } ;
struct g_raid_disk {int dummy; } ;

/* Variables and functions */
#define  G_RAID_DISK_E_DISCONNECTED 128 
 int /*<<< orphan*/  G_RAID_DISK_S_NONE ; 
 int /*<<< orphan*/  g_raid_change_disk_state (struct g_raid_disk*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_destroy_disk (struct g_raid_disk*) ; 
 int /*<<< orphan*/  g_raid_destroy_node (struct g_raid_softc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_md_promise_purge_volumes (struct g_raid_softc*) ; 
 int /*<<< orphan*/  g_raid_md_promise_refill (struct g_raid_softc*) ; 
 int /*<<< orphan*/  g_raid_md_write_promise (struct g_raid_md_object*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_raid_ndisks (struct g_raid_softc*,int) ; 

__attribute__((used)) static int
g_raid_md_event_promise(struct g_raid_md_object *md,
    struct g_raid_disk *disk, u_int event)
{
	struct g_raid_softc *sc;

	sc = md->mdo_softc;
	if (disk == NULL)
		return (-1);
	switch (event) {
	case G_RAID_DISK_E_DISCONNECTED:
		/* Delete disk. */
		g_raid_change_disk_state(disk, G_RAID_DISK_S_NONE);
		g_raid_destroy_disk(disk);
		g_raid_md_promise_purge_volumes(sc);

		/* Write updated metadata to all disks. */
		g_raid_md_write_promise(md, NULL, NULL, NULL);

		/* Check if anything left. */
		if (g_raid_ndisks(sc, -1) == 0)
			g_raid_destroy_node(sc, 0);
		else
			g_raid_md_promise_refill(sc);
		return (0);
	}
	return (-2);
}