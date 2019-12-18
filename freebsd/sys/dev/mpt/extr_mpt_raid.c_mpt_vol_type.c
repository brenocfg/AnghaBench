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
struct mpt_raid_volume {TYPE_1__* config_page; } ;
struct TYPE_2__ {int VolumeType; } ;

/* Variables and functions */
#define  MPI_RAID_VOL_TYPE_IM 130 
#define  MPI_RAID_VOL_TYPE_IME 129 
#define  MPI_RAID_VOL_TYPE_IS 128 

__attribute__((used)) static const char *
mpt_vol_type(struct mpt_raid_volume *vol)
{
	switch (vol->config_page->VolumeType) {
	case MPI_RAID_VOL_TYPE_IS:
		return ("RAID-0");
	case MPI_RAID_VOL_TYPE_IME:
		return ("RAID-1E");
	case MPI_RAID_VOL_TYPE_IM:
		return ("RAID-1");
	default:
		return ("Unknown");
	}
}