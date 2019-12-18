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
struct TYPE_3__ {int State; } ;
struct TYPE_4__ {TYPE_1__ PhysDiskStatus; } ;
struct mpt_raid_disk {TYPE_2__ config_page; } ;

/* Variables and functions */
#define  MPI_PHYSDISK0_STATUS_FAILED 135 
#define  MPI_PHYSDISK0_STATUS_FAILED_REQUESTED 134 
#define  MPI_PHYSDISK0_STATUS_INITIALIZING 133 
#define  MPI_PHYSDISK0_STATUS_MISSING 132 
#define  MPI_PHYSDISK0_STATUS_NOT_COMPATIBLE 131 
#define  MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED 130 
#define  MPI_PHYSDISK0_STATUS_ONLINE 129 
#define  MPI_PHYSDISK0_STATUS_OTHER_OFFLINE 128 

__attribute__((used)) static const char *
mpt_disk_state(struct mpt_raid_disk *disk)
{
	switch (disk->config_page.PhysDiskStatus.State) {
	case MPI_PHYSDISK0_STATUS_ONLINE:
		return ("Online");
	case MPI_PHYSDISK0_STATUS_MISSING:
		return ("Missing");
	case MPI_PHYSDISK0_STATUS_NOT_COMPATIBLE:
		return ("Incompatible");
	case MPI_PHYSDISK0_STATUS_FAILED:
		return ("Failed");
	case MPI_PHYSDISK0_STATUS_INITIALIZING:
		return ("Initializing");
	case MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED:
		return ("Offline Requested");
	case MPI_PHYSDISK0_STATUS_FAILED_REQUESTED:
		return ("Failed per Host Request");
	case MPI_PHYSDISK0_STATUS_OTHER_OFFLINE:
		return ("Offline");
	default:
		return ("Unknown");
	}
}