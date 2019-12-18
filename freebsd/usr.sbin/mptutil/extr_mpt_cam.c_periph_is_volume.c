#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct periph_match_result {scalar_t__ target_id; } ;
struct TYPE_5__ {int NumActiveVolumes; TYPE_1__* RaidVolume; } ;
struct TYPE_4__ {scalar_t__ VolumeBus; scalar_t__ VolumeID; } ;
typedef  TYPE_1__ CONFIG_PAGE_IOC_2_RAID_VOL ;
typedef  TYPE_2__ CONFIG_PAGE_IOC_2 ;

/* Variables and functions */

__attribute__((used)) static int
periph_is_volume(CONFIG_PAGE_IOC_2 *ioc2, struct periph_match_result *r)
{
	CONFIG_PAGE_IOC_2_RAID_VOL *vol;
	int i;

	if (ioc2 == NULL)
		return (0);
	vol = ioc2->RaidVolume;
	for (i = 0; i < ioc2->NumActiveVolumes; vol++, i++) {
		if (vol->VolumeBus == 0 && vol->VolumeID == r->target_id)
			return (1);
	}
	return (0);
}