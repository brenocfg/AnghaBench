#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct g_raid_volume {int /*<<< orphan*/  v_softc; } ;
struct g_raid_tr_raid1_object {int trso_flags; struct g_raid_subdisk* trso_failed_sd; } ;
struct g_raid_tr_object {struct g_raid_volume* tro_volume; } ;
struct g_raid_subdisk {scalar_t__ sd_rebuild_pos; scalar_t__ sd_size; scalar_t__ sd_disk; int /*<<< orphan*/  sd_pos; TYPE_1__* sd_volume; } ;
typedef  int /*<<< orphan*/  off_t ;
struct TYPE_2__ {int /*<<< orphan*/  v_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  MIN (int /*<<< orphan*/ ,scalar_t__) ; 
 int TR_RAID1_F_ABORT ; 
 int TR_RAID1_F_DOING_SOME ; 
 int TR_RAID1_F_LOCKED ; 
 int /*<<< orphan*/  g_raid1_rebuild_slab ; 
 char* g_raid_get_diskname (scalar_t__) ; 
 int /*<<< orphan*/  g_raid_tr_raid1_rebuild_done (struct g_raid_tr_raid1_object*) ; 
 int /*<<< orphan*/  g_raid_unlock_range (struct g_raid_volume*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid_tr_raid1_rebuild_abort(struct g_raid_tr_object *tr)
{
	struct g_raid_tr_raid1_object *trs;
	struct g_raid_subdisk *sd;
	struct g_raid_volume *vol;
	off_t len;

	vol = tr->tro_volume;
	trs = (struct g_raid_tr_raid1_object *)tr;
	sd = trs->trso_failed_sd;
	if (trs->trso_flags & TR_RAID1_F_DOING_SOME) {
		G_RAID_DEBUG1(1, vol->v_softc,
		    "Subdisk %s:%d-%s rebuild is aborting.",
		    sd->sd_volume->v_name, sd->sd_pos,
		    sd->sd_disk ? g_raid_get_diskname(sd->sd_disk) : "[none]");
		trs->trso_flags |= TR_RAID1_F_ABORT;
	} else {
		G_RAID_DEBUG1(0, vol->v_softc,
		    "Subdisk %s:%d-%s rebuild aborted.",
		    sd->sd_volume->v_name, sd->sd_pos,
		    sd->sd_disk ? g_raid_get_diskname(sd->sd_disk) : "[none]");
		trs->trso_flags &= ~TR_RAID1_F_ABORT;
		if (trs->trso_flags & TR_RAID1_F_LOCKED) {
			trs->trso_flags &= ~TR_RAID1_F_LOCKED;
			len = MIN(g_raid1_rebuild_slab,
			    sd->sd_size - sd->sd_rebuild_pos);
			g_raid_unlock_range(tr->tro_volume,
			    sd->sd_rebuild_pos, len);
		}
		g_raid_tr_raid1_rebuild_done(trs);
	}
}