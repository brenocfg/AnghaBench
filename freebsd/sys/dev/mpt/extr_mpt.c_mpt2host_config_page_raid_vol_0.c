#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  Reserved; } ;
struct TYPE_5__ {int /*<<< orphan*/  Settings; } ;
struct TYPE_4__ {int /*<<< orphan*/  Reserved; } ;
typedef  int /*<<< orphan*/  CONFIG_PAGE_RAID_VOL_0 ;

/* Variables and functions */
 int MPI_RAID_VOL_PAGE_0_PHYSDISK_MAX ; 
 int /*<<< orphan*/  MPT_2_HOST16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPT_2_HOST32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MaxLBA ; 
 int /*<<< orphan*/  MaxLBAHigh ; 
 TYPE_3__* PhysDisk ; 
 int /*<<< orphan*/  Reserved2 ; 
 int /*<<< orphan*/  Reserved3 ; 
 int /*<<< orphan*/  StripeSize ; 
 TYPE_2__ VolumeSettings ; 
 TYPE_1__ VolumeStatus ; 

void
mpt2host_config_page_raid_vol_0(CONFIG_PAGE_RAID_VOL_0 *volp)
{
	int i;

	MPT_2_HOST16(volp, VolumeStatus.Reserved);
	MPT_2_HOST16(volp, VolumeSettings.Settings);
	MPT_2_HOST32(volp, MaxLBA);
	MPT_2_HOST32(volp, MaxLBAHigh);
	MPT_2_HOST32(volp, StripeSize);
	MPT_2_HOST32(volp, Reserved2);
	MPT_2_HOST32(volp, Reserved3);
	for (i = 0; i < MPI_RAID_VOL_PAGE_0_PHYSDISK_MAX; i++) {
		MPT_2_HOST16(volp, PhysDisk[i].Reserved);
	}
}