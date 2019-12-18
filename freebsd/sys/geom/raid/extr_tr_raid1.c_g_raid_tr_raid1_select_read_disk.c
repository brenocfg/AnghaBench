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
struct g_raid_volume {int v_disks_count; struct g_raid_subdisk* v_subdisks; } ;
struct g_raid_subdisk {scalar_t__ sd_state; scalar_t__ sd_rebuild_pos; int /*<<< orphan*/  sd_recovery; } ;
struct bio {scalar_t__ bio_offset; scalar_t__ bio_length; } ;

/* Variables and functions */
 scalar_t__ ABS (scalar_t__) ; 
 int G_RAID_SUBDISK_LOAD (struct g_raid_subdisk*) ; 
 int G_RAID_SUBDISK_LOAD_SCALE ; 
 scalar_t__ G_RAID_SUBDISK_POS (struct g_raid_subdisk*) ; 
 scalar_t__ G_RAID_SUBDISK_S_ACTIVE ; 
 scalar_t__ G_RAID_SUBDISK_S_REBUILD ; 
 scalar_t__ G_RAID_SUBDISK_S_RESYNC ; 
 scalar_t__ G_RAID_SUBDISK_TRACK_SIZE ; 
 int INT_MAX ; 
 int min (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct g_raid_subdisk *
g_raid_tr_raid1_select_read_disk(struct g_raid_volume *vol, struct bio *bp,
    u_int mask)
{
	struct g_raid_subdisk *sd, *best;
	int i, prio, bestprio;

	best = NULL;
	bestprio = INT_MAX;
	for (i = 0; i < vol->v_disks_count; i++) {
		sd = &vol->v_subdisks[i];
		if (sd->sd_state != G_RAID_SUBDISK_S_ACTIVE &&
		    ((sd->sd_state != G_RAID_SUBDISK_S_REBUILD &&
		      sd->sd_state != G_RAID_SUBDISK_S_RESYNC) ||
		     bp->bio_offset + bp->bio_length > sd->sd_rebuild_pos))
			continue;
		if ((mask & (1 << i)) != 0)
			continue;
		prio = G_RAID_SUBDISK_LOAD(sd);
		prio += min(sd->sd_recovery, 255) << 22;
		prio += (G_RAID_SUBDISK_S_ACTIVE - sd->sd_state) << 16;
		/* If disk head is precisely in position - highly prefer it. */
		if (G_RAID_SUBDISK_POS(sd) == bp->bio_offset)
			prio -= 2 * G_RAID_SUBDISK_LOAD_SCALE;
		else
		/* If disk head is close to position - prefer it. */
		if (ABS(G_RAID_SUBDISK_POS(sd) - bp->bio_offset) <
		    G_RAID_SUBDISK_TRACK_SIZE)
			prio -= 1 * G_RAID_SUBDISK_LOAD_SCALE;
		if (prio < bestprio) {
			best = sd;
			bestprio = prio;
		}
	}
	return (best);
}