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
struct g_raid_disk {int d_state; int /*<<< orphan*/  d_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_disk_state2str (int) ; 
 int /*<<< orphan*/  g_raid_get_diskname (struct g_raid_disk*) ; 
 int /*<<< orphan*/  g_raid_report_disk_state (struct g_raid_disk*) ; 

void
g_raid_change_disk_state(struct g_raid_disk *disk, int state)
{

	G_RAID_DEBUG1(0, disk->d_softc, "Disk %s state changed from %s to %s.",
	    g_raid_get_diskname(disk),
	    g_raid_disk_state2str(disk->d_state),
	    g_raid_disk_state2str(state));
	disk->d_state = state;
	g_raid_report_disk_state(disk);
}