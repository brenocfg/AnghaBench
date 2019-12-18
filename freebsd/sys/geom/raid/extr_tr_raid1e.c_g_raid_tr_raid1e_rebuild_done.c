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
struct TYPE_2__ {struct g_raid_volume* tro_volume; } ;
struct g_raid_tr_raid1e_object {struct g_raid_subdisk* trso_failed_sd; scalar_t__ trso_recover_slabs; int /*<<< orphan*/  trso_type; int /*<<< orphan*/  trso_flags; int /*<<< orphan*/ * trso_buffer; TYPE_1__ trso_base; } ;
struct g_raid_subdisk {int /*<<< orphan*/  sd_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_TR_RAID1E ; 
 int /*<<< orphan*/  TR_RAID1E_F_DOING_SOME ; 
 int /*<<< orphan*/  TR_RAID1E_NONE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_raid_tr_update_state_raid1e (struct g_raid_volume*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_raid_write_metadata (int /*<<< orphan*/ ,struct g_raid_volume*,struct g_raid_subdisk*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
g_raid_tr_raid1e_rebuild_done(struct g_raid_tr_raid1e_object *trs)
{
	struct g_raid_volume *vol;
	struct g_raid_subdisk *sd;

	vol = trs->trso_base.tro_volume;
	sd = trs->trso_failed_sd;
	g_raid_write_metadata(vol->v_softc, vol, sd, sd->sd_disk);
	free(trs->trso_buffer, M_TR_RAID1E);
	trs->trso_buffer = NULL;
	trs->trso_flags &= ~TR_RAID1E_F_DOING_SOME;
	trs->trso_type = TR_RAID1E_NONE;
	trs->trso_recover_slabs = 0;
	trs->trso_failed_sd = NULL;
	g_raid_tr_update_state_raid1e(vol, NULL);
}