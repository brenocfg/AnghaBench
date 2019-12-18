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
struct mpt_raid_volume {TYPE_2__* config_page; } ;
struct TYPE_3__ {int State; } ;
struct TYPE_4__ {TYPE_1__ VolumeStatus; } ;

/* Variables and functions */
#define  MPI_RAIDVOL0_STATUS_STATE_DEGRADED 130 
#define  MPI_RAIDVOL0_STATUS_STATE_FAILED 129 
#define  MPI_RAIDVOL0_STATUS_STATE_OPTIMAL 128 

__attribute__((used)) static const char *
mpt_vol_state(struct mpt_raid_volume *vol)
{
	switch (vol->config_page->VolumeStatus.State) {
	case MPI_RAIDVOL0_STATUS_STATE_OPTIMAL:
		return ("Optimal");
	case MPI_RAIDVOL0_STATUS_STATE_DEGRADED:
		return ("Degraded");
	case MPI_RAIDVOL0_STATUS_STATE_FAILED:
		return ("Failed");
	default:
		return ("Unknown");
	}
}