#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct g_raid_tr_raid1e_object {struct g_raid_subdisk* trso_failed_sd; } ;
struct g_raid_tr_object {TYPE_1__* tro_volume; } ;
struct g_raid_subdisk {scalar_t__ sd_rebuild_pos; scalar_t__ sd_disk; int /*<<< orphan*/  sd_pos; TYPE_2__* sd_volume; } ;
struct TYPE_4__ {int /*<<< orphan*/  v_name; } ;
struct TYPE_3__ {int /*<<< orphan*/  v_softc; } ;

/* Variables and functions */
 int /*<<< orphan*/  G_RAID_DEBUG1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  G_RAID_SUBDISK_S_ACTIVE ; 
 int /*<<< orphan*/  g_raid_change_subdisk_state (struct g_raid_subdisk*,int /*<<< orphan*/ ) ; 
 char* g_raid_get_diskname (scalar_t__) ; 
 int /*<<< orphan*/  g_raid_tr_raid1e_rebuild_done (struct g_raid_tr_raid1e_object*) ; 

__attribute__((used)) static void
g_raid_tr_raid1e_rebuild_finish(struct g_raid_tr_object *tr)
{
	struct g_raid_tr_raid1e_object *trs;
	struct g_raid_subdisk *sd;

	trs = (struct g_raid_tr_raid1e_object *)tr;
	sd = trs->trso_failed_sd;
	G_RAID_DEBUG1(0, tr->tro_volume->v_softc,
	    "Subdisk %s:%d-%s rebuild completed.",
	    sd->sd_volume->v_name, sd->sd_pos,
	    sd->sd_disk ? g_raid_get_diskname(sd->sd_disk) : "[none]");
	g_raid_change_subdisk_state(sd, G_RAID_SUBDISK_S_ACTIVE);
	sd->sd_rebuild_pos = 0;
	g_raid_tr_raid1e_rebuild_done(trs);
}