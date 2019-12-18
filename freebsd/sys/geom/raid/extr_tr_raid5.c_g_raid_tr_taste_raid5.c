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
typedef  scalar_t__ u_int ;
struct g_raid_volume {int dummy; } ;
struct g_raid_tr_raid5_object {int trso_starting; } ;
struct g_raid_tr_object {TYPE_1__* tro_volume; } ;
struct TYPE_2__ {scalar_t__ v_raid_level_qualifier; scalar_t__ v_raid_level; } ;

/* Variables and functions */
 int G_RAID_TR_TASTE_FAIL ; 
 int G_RAID_TR_TASTE_SUCCEED ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R4P0 ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R4PN ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R5LA ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R5LS ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R5RA ; 
 scalar_t__ G_RAID_VOLUME_RLQ_R5RS ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID4 ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID5 ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID5E ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID5EE ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID5R ; 
 scalar_t__ G_RAID_VOLUME_RL_RAID6 ; 
 scalar_t__ G_RAID_VOLUME_RL_RAIDMDF ; 

__attribute__((used)) static int
g_raid_tr_taste_raid5(struct g_raid_tr_object *tr, struct g_raid_volume *vol)
{
	struct g_raid_tr_raid5_object *trs;
	u_int qual;

	trs = (struct g_raid_tr_raid5_object *)tr;
	qual = tr->tro_volume->v_raid_level_qualifier;
	if (tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAID4 &&
	    (qual == G_RAID_VOLUME_RLQ_R4P0 ||
	     qual == G_RAID_VOLUME_RLQ_R4PN)) {
		/* RAID4 */
	} else if ((tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAID5 ||
	     tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAID5E ||
	     tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAID5EE ||
	     tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAID5R ||
	     tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAID6 ||
	     tr->tro_volume->v_raid_level == G_RAID_VOLUME_RL_RAIDMDF) &&
	    (qual == G_RAID_VOLUME_RLQ_R5RA ||
	     qual == G_RAID_VOLUME_RLQ_R5RS ||
	     qual == G_RAID_VOLUME_RLQ_R5LA ||
	     qual == G_RAID_VOLUME_RLQ_R5LS)) {
		/* RAID5/5E/5EE/5R/6/MDF */
	} else
		return (G_RAID_TR_TASTE_FAIL);
	trs->trso_starting = 1;
	return (G_RAID_TR_TASTE_SUCCEED);
}