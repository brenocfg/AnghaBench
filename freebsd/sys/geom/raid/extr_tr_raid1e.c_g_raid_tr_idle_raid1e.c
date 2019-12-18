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
struct g_raid_volume {int v_disks_count; int /*<<< orphan*/  v_strip_size; } ;
struct g_raid_tr_raid1e_object {scalar_t__ trso_type; int /*<<< orphan*/  trso_recover_slabs; int /*<<< orphan*/  trso_fair_io; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;

/* Variables and functions */
 int N ; 
 scalar_t__ TR_RAID1E_REBUILD ; 
 int /*<<< orphan*/  g_raid1e_rebuild_cluster_idle ; 
 int /*<<< orphan*/  g_raid1e_rebuild_fair_io ; 
 int /*<<< orphan*/  g_raid1e_rebuild_slab ; 
 int /*<<< orphan*/  g_raid_tr_raid1e_rebuild_some (struct g_raid_tr_object*) ; 

__attribute__((used)) static int
g_raid_tr_idle_raid1e(struct g_raid_tr_object *tr)
{
	struct g_raid_tr_raid1e_object *trs;
	struct g_raid_volume *vol;

	vol = tr->tro_volume;
	trs = (struct g_raid_tr_raid1e_object *)tr;
	trs->trso_fair_io = g_raid1e_rebuild_fair_io;
	trs->trso_recover_slabs = g_raid1e_rebuild_cluster_idle;
	/* Compensate short rebuild I/Os. */
	if ((vol->v_disks_count % N) != 0 &&
	    vol->v_strip_size < g_raid1e_rebuild_slab) {
		trs->trso_recover_slabs *= g_raid1e_rebuild_slab;
		trs->trso_recover_slabs /= vol->v_strip_size;
	}
	if (trs->trso_type == TR_RAID1E_REBUILD)
		g_raid_tr_raid1e_rebuild_some(tr);
	return (0);
}