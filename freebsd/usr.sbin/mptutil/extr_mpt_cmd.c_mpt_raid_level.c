#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int U8 ;

/* Variables and functions */
#define  MPI_RAID_VOL_TYPE_IM 134 
#define  MPI_RAID_VOL_TYPE_IME 133 
#define  MPI_RAID_VOL_TYPE_IS 132 
#define  MPI_RAID_VOL_TYPE_RAID_10 131 
#define  MPI_RAID_VOL_TYPE_RAID_5 130 
#define  MPI_RAID_VOL_TYPE_RAID_50 129 
#define  MPI_RAID_VOL_TYPE_RAID_6 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
mpt_raid_level(U8 VolumeType)
{
	static char buf[16];

	switch (VolumeType) {
	case MPI_RAID_VOL_TYPE_IS:
		return ("RAID-0");
	case MPI_RAID_VOL_TYPE_IM:
		return ("RAID-1");
	case MPI_RAID_VOL_TYPE_IME:
		return ("RAID-1E");
	case MPI_RAID_VOL_TYPE_RAID_5:
		return ("RAID-5");
	case MPI_RAID_VOL_TYPE_RAID_6:
		return ("RAID-6");
	case MPI_RAID_VOL_TYPE_RAID_10:
		return ("RAID-10");
	case MPI_RAID_VOL_TYPE_RAID_50:
		return ("RAID-50");
	default:
		sprintf(buf, "LVL 0x%02x", VolumeType);
		return (buf);
	}
}