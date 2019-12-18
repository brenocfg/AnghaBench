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
typedef  int /*<<< orphan*/  vm_offset_t ;
struct g_raid_volume {int v_disks_count; struct g_raid_subdisk* v_subdisks; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {int sd_state; int /*<<< orphan*/  sd_rebuild_pos; } ;
typedef  int /*<<< orphan*/  off_t ;

/* Variables and functions */
#define  G_RAID_SUBDISK_S_ACTIVE 131 
#define  G_RAID_SUBDISK_S_REBUILD 130 
#define  G_RAID_SUBDISK_S_RESYNC 129 
#define  G_RAID_SUBDISK_S_STALE 128 
 int g_raid_subdisk_kerneldump (struct g_raid_subdisk*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
g_raid_tr_kerneldump_raid1(struct g_raid_tr_object *tr,
    void *virtual, vm_offset_t physical, off_t offset, size_t length)
{
	struct g_raid_volume *vol;
	struct g_raid_subdisk *sd;
	int error, i, ok;

	vol = tr->tro_volume;
	error = 0;
	ok = 0;
	for (i = 0; i < vol->v_disks_count; i++) {
		sd = &vol->v_subdisks[i];
		switch (sd->sd_state) {
		case G_RAID_SUBDISK_S_ACTIVE:
			break;
		case G_RAID_SUBDISK_S_REBUILD:
			/*
			 * When rebuilding, only part of this subdisk is
			 * writable, the rest will be written as part of the
			 * that process.
			 */
			if (offset >= sd->sd_rebuild_pos)
				continue;
			break;
		case G_RAID_SUBDISK_S_STALE:
		case G_RAID_SUBDISK_S_RESYNC:
			/*
			 * Resyncing still writes on the theory that the
			 * resync'd disk is very close and writing it will
			 * keep it that way better if we keep up while
			 * resyncing.
			 */
			break;
		default:
			continue;
		}
		error = g_raid_subdisk_kerneldump(sd,
		    virtual, physical, offset, length);
		if (error == 0)
			ok++;
	}
	return (ok > 0 ? 0 : error);
}