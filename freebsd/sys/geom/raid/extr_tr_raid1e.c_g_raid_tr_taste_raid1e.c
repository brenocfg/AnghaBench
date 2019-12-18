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
struct g_raid_volume {int dummy; } ;
struct g_raid_tr_raid1e_object {int trso_starting; } ;
struct g_raid_tr_object {TYPE_1__* tro_volume; } ;
struct TYPE_2__ {scalar_t__ v_raid_level; scalar_t__ v_raid_level_qualifier; } ;

/* Variables and functions */
 int G_RAID_TR_TASTE_FAIL ; 
 int G_RAID_TR_TASTE_SUCCEED ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R1EA ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID1E ; 

__attribute__((used)) static int
g_raid_tr_taste_raid1e(struct g_raid_tr_object *tr, struct g_raid_volume *vol)
{
	struct g_raid_tr_raid1e_object *trs;

	trs = (struct g_raid_tr_raid1e_object *)tr;
	if (tr->tro_volume->v_raid_level != G_RAID_VOLUME_RL_RAID1E ||
	    tr->tro_volume->v_raid_level_qualifier != G_RAID_VOLUME_RLQ_R1EA)
		return (G_RAID_TR_TASTE_FAIL);
	trs->trso_starting = 1;
	return (G_RAID_TR_TASTE_SUCCEED);
}