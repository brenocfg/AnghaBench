#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int State; int Flags; } ;
struct TYPE_5__ {int /*<<< orphan*/  HotSparePool; } ;
struct TYPE_7__ {TYPE_2__ PhysDiskStatus; TYPE_1__ PhysDiskSettings; } ;
typedef  TYPE_3__ CONFIG_PAGE_RAID_PHYS_DISK_0 ;

/* Variables and functions */
#define  MPI_PHYSDISK0_STATUS_FAILED 135 
#define  MPI_PHYSDISK0_STATUS_FAILED_REQUESTED 134 
 int MPI_PHYSDISK0_STATUS_FLAG_OUT_OF_SYNC ; 
#define  MPI_PHYSDISK0_STATUS_INITIALIZING 133 
#define  MPI_PHYSDISK0_STATUS_MISSING 132 
#define  MPI_PHYSDISK0_STATUS_NOT_COMPATIBLE 131 
#define  MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED 130 
#define  MPI_PHYSDISK0_STATUS_ONLINE 129 
#define  MPI_PHYSDISK0_STATUS_OTHER_OFFLINE 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
mpt_pdstate(CONFIG_PAGE_RAID_PHYS_DISK_0 *info)
{
	static char buf[16];

	switch (info->PhysDiskStatus.State) {
	case MPI_PHYSDISK0_STATUS_ONLINE:
		if ((info->PhysDiskStatus.Flags &
		    MPI_PHYSDISK0_STATUS_FLAG_OUT_OF_SYNC) &&
		    info->PhysDiskSettings.HotSparePool == 0)
			return ("REBUILD");
		else
			return ("ONLINE");
	case MPI_PHYSDISK0_STATUS_MISSING:
		return ("MISSING");
	case MPI_PHYSDISK0_STATUS_NOT_COMPATIBLE:
		return ("NOT COMPATIBLE");
	case MPI_PHYSDISK0_STATUS_FAILED:
		return ("FAILED");
	case MPI_PHYSDISK0_STATUS_INITIALIZING:
		return ("INITIALIZING");
	case MPI_PHYSDISK0_STATUS_OFFLINE_REQUESTED:
		return ("OFFLINE REQUESTED");
	case MPI_PHYSDISK0_STATUS_FAILED_REQUESTED:
		return ("FAILED REQUESTED");
	case MPI_PHYSDISK0_STATUS_OTHER_OFFLINE:
		return ("OTHER OFFLINE");
	default:
		sprintf(buf, "PSTATE 0x%02x", info->PhysDiskStatus.State);
		return (buf);
	}
}