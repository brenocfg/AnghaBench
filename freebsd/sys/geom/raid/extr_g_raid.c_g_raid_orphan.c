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
struct g_raid_disk {int dummy; } ;
struct g_consumer {struct g_raid_disk* private; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DISK_E_DISCONNECTED ; 
 int /*<<< orphan*/  G_RAID_EVENT_DISK ; 
 int /*<<< orphan*/  g_raid_event_send (struct g_raid_disk*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_topology_assert () ; 

__attribute__((used)) static void
g_raid_orphan(struct g_consumer *cp)
{
	struct g_raid_disk *disk;

	g_topology_assert();

	disk = cp->private;
	if (disk == NULL)
		return;
	g_raid_event_send(disk, G_RAID_DISK_E_DISCONNECTED,
	    G_RAID_EVENT_DISK);
}