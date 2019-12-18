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
typedef  scalar_t__ target_id_t ;
struct mpt_softc {TYPE_1__* ioc_page2; } ;
struct TYPE_4__ {scalar_t__ VolumeID; } ;
struct TYPE_3__ {scalar_t__ MaxPhysDisks; int NumActiveVolumes; TYPE_2__* RaidVolume; } ;
typedef  TYPE_2__ CONFIG_PAGE_IOC_2_RAID_VOL ;

/* Variables and functions */

int
mpt_is_raid_volume(struct mpt_softc *mpt, target_id_t tgt)
{
	CONFIG_PAGE_IOC_2_RAID_VOL *ioc_vol;
	CONFIG_PAGE_IOC_2_RAID_VOL *ioc_last_vol;

	if (mpt->ioc_page2 == NULL || mpt->ioc_page2->MaxPhysDisks == 0) {
		return (0);
	}
	ioc_vol = mpt->ioc_page2->RaidVolume;
	ioc_last_vol = ioc_vol + mpt->ioc_page2->NumActiveVolumes;
	for (;ioc_vol != ioc_last_vol; ioc_vol++) {
		if (ioc_vol->VolumeID == tgt) {
			return (1);
		}
	}
	return (0);
}