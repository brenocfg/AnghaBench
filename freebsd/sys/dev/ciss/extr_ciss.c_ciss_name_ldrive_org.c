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
#define  CISS_LDRIVE_RAID0 133 
#define  CISS_LDRIVE_RAID1 132 
#define  CISS_LDRIVE_RAID4 131 
#define  CISS_LDRIVE_RAID5 130 
#define  CISS_LDRIVE_RAID51 129 
#define  CISS_LDRIVE_RAIDADG 128 

__attribute__((used)) static const char *
ciss_name_ldrive_org(int org)
{
    switch(org) {
    case CISS_LDRIVE_RAID0:
	return("RAID 0");
    case CISS_LDRIVE_RAID1:
	return("RAID 1(1+0)");
    case CISS_LDRIVE_RAID4:
	return("RAID 4");
    case CISS_LDRIVE_RAID5:
	return("RAID 5");
    case CISS_LDRIVE_RAID51:
	return("RAID 5+1");
    case CISS_LDRIVE_RAIDADG:
	return("RAID ADG");
    }
    return("unknown");
}