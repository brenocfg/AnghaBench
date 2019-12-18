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
typedef  int uint8_t ;

/* Variables and functions */
#define  DDF_CONCAT 137 
#define  DDF_JBOD 136 
#define  DDF_RAID0 135 
#define  DDF_RAID1 134 
#define  DDF_RAID1E 133 
#define  DDF_RAID3 132 
#define  DDF_RAID5 131 
#define  DDF_RAID5E 130 
#define  DDF_RAID5EE 129 
#define  DDF_RAID6 128 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 

const char *
mfi_raid_level(uint8_t primary_level, uint8_t secondary_level)
{
	static char buf[16];

	switch (primary_level) {
	case DDF_RAID0:
		return ("RAID-0");
	case DDF_RAID1:
		if (secondary_level != 0)
			return ("RAID-10");
		else
			return ("RAID-1");
	case DDF_RAID1E:
		return ("RAID-1E");
	case DDF_RAID3:
		return ("RAID-3");
	case DDF_RAID5:
		if (secondary_level != 0)
			return ("RAID-50");
		else
			return ("RAID-5");
	case DDF_RAID5E:
		return ("RAID-5E");
	case DDF_RAID5EE:
		return ("RAID-5EE");
	case DDF_RAID6:
		if (secondary_level != 0)
			return ("RAID-60");
		else
			return ("RAID-6");
	case DDF_JBOD:
		return ("JBOD");
	case DDF_CONCAT:
		return ("CONCAT");
	default:
		sprintf(buf, "LVL 0x%02x", primary_level);
		return (buf);
	}
}