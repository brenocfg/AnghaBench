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
struct g_raid_volume {scalar_t__ v_disks_count; } ;
struct g_raid_subdisk {scalar_t__ sd_state; struct g_raid_volume* sd_volume; } ;
struct g_raid_softc {int dummy; } ;
struct g_raid_disk {int dummy; } ;

/* Variables and functions */
 scalar_t__ G_RAID_SUBDISK_S_ACTIVE ; 
 scalar_t__ G_RAID_SUBDISK_S_RESYNC ; 
 scalar_t__ G_RAID_SUBDISK_S_STALE ; 
 scalar_t__ G_RAID_SUBDISK_S_UNINITIALIZED ; 
 int /*<<< orphan*/  g_raid_fail_disk (struct g_raid_softc*,struct g_raid_subdisk*,struct g_raid_disk*) ; 
 scalar_t__ g_raid_nsubdisks (struct g_raid_volume*,scalar_t__) ; 

__attribute__((used)) static void
g_raid_tr_raid1e_fail_disk(struct g_raid_softc *sc, struct g_raid_subdisk *sd,
    struct g_raid_disk *disk)
{
	struct g_raid_volume *vol;

	vol = sd->sd_volume;
	/*
	 * We don't fail the last disk in the pack, since it still has decent
	 * data on it and that's better than failing the disk if it is the root
	 * file system.
	 *
	 * XXX should this be controlled via a tunable?  It makes sense for
	 * the volume that has / on it.  I can't think of a case where we'd
	 * want the volume to go away on this kind of event.
	 */
	if ((g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_ACTIVE) +
	     g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_RESYNC) +
	     g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_STALE) +
	     g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_UNINITIALIZED) <
	     vol->v_disks_count) &&
	    (sd->sd_state >= G_RAID_SUBDISK_S_UNINITIALIZED))
		return;
	g_raid_fail_disk(sc, sd, disk);
}