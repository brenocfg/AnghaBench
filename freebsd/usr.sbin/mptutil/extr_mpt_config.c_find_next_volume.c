#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct config_id_state {scalar_t__ target_id; int nsdisks; TYPE_4__* ioc2; TYPE_3__* list; TYPE_1__* sdisks; } ;
typedef  scalar_t__ U8 ;
struct TYPE_10__ {scalar_t__ VolumeID; } ;
struct TYPE_9__ {int NumActiveVolumes; TYPE_5__* RaidVolume; } ;
struct TYPE_8__ {int ndrives; TYPE_2__** drives; } ;
struct TYPE_7__ {scalar_t__ PhysDiskID; } ;
struct TYPE_6__ {scalar_t__ target; } ;
typedef  TYPE_5__ CONFIG_PAGE_IOC_2_RAID_VOL ;

/* Variables and functions */

__attribute__((used)) static U8
find_next_volume(struct config_id_state *state)
{
	CONFIG_PAGE_IOC_2_RAID_VOL *vol;
	int i;

restart:
	/* Assume the current one is used. */
	state->target_id++;

	/* Search drives first. */
	for (i = 0; i < state->nsdisks; i++)
		if (state->sdisks[i].target == state->target_id)
			goto restart;
	for (i = 0; i < state->list->ndrives; i++)
		if (state->list->drives[i]->PhysDiskID == state->target_id)
			goto restart;

	/* Search volumes second. */
	vol = state->ioc2->RaidVolume;
	for (i = 0; i < state->ioc2->NumActiveVolumes; vol++, i++)
		if (vol->VolumeID == state->target_id)
			goto restart;

	return (state->target_id);
}