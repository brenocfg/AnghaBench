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
struct g_raid_volume {int /*<<< orphan*/  v_state; } ;
struct g_raid_tr_raid1e_object {int trso_type; struct g_raid_subdisk* trso_failed_sd; scalar_t__ trso_stopping; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_SUBDISK_S_NEW ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_REBUILD ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_RESYNC ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_STALE ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_UNINITIALIZED ; 
 int /*<<< orphan*/  G_RAID_VOLUME_S_DEGRADED ; 
#define  TR_RAID1E_NONE 130 
#define  TR_RAID1E_REBUILD 129 
#define  TR_RAID1E_RESYNC 128 
 int g_raid_nsubdisks (struct g_raid_volume*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_tr_raid1e_rebuild_abort (struct g_raid_tr_object*) ; 
 int /*<<< orphan*/  g_raid_tr_raid1e_rebuild_start (struct g_raid_tr_object*) ; 

__attribute__((used)) static void
g_raid_tr_raid1e_maybe_rebuild(struct g_raid_tr_object *tr,
    struct g_raid_subdisk *sd)
{
	struct g_raid_volume *vol;
	struct g_raid_tr_raid1e_object *trs;
	int nr;
	
	vol = tr->tro_volume;
	trs = (struct g_raid_tr_raid1e_object *)tr;
	if (trs->trso_stopping)
		return;
	nr = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_REBUILD) +
	    g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_RESYNC);
	switch(trs->trso_type) {
	case TR_RAID1E_NONE:
		if (vol->v_state < G_RAID_VOLUME_S_DEGRADED)
			return;
		if (nr == 0) {
			nr = g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_NEW) +
			    g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_STALE) +
			    g_raid_nsubdisks(vol, G_RAID_SUBDISK_S_UNINITIALIZED);
			if (nr == 0)
				return;
		}
		g_raid_tr_raid1e_rebuild_start(tr);
		break;
	case TR_RAID1E_REBUILD:
		if (vol->v_state < G_RAID_VOLUME_S_DEGRADED || nr == 0 ||
		    trs->trso_failed_sd == sd)
			g_raid_tr_raid1e_rebuild_abort(tr);
		break;
	case TR_RAID1E_RESYNC:
		break;
	}
}