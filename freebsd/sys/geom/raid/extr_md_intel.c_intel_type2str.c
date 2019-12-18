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

/* Variables and functions */
#define  INTEL_T_RAID0 130 
#define  INTEL_T_RAID1 129 
#define  INTEL_T_RAID5 128 

__attribute__((used)) static char *
intel_type2str(int type)
{

	switch (type) {
	case INTEL_T_RAID0:
		return ("RAID0");
	case INTEL_T_RAID1:
		return ("RAID1");
	case INTEL_T_RAID5:
		return ("RAID5");
	default:
		return ("UNKNOWN");
	}
}