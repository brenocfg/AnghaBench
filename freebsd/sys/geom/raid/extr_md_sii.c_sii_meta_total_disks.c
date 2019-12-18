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
struct sii_raid_conf {int type; int raid0_disks; int raid1_disks; } ;

/* Variables and functions */
#define  SII_T_CONCAT 134 
#define  SII_T_JBOD 133 
#define  SII_T_RAID0 132 
#define  SII_T_RAID01 131 
#define  SII_T_RAID1 130 
#define  SII_T_RAID5 129 
#define  SII_T_SPARE 128 

__attribute__((used)) static int
sii_meta_total_disks(struct sii_raid_conf *meta)
{

	switch (meta->type) {
	case SII_T_RAID0:
	case SII_T_RAID5:
	case SII_T_CONCAT:
		return (meta->raid0_disks);
	case SII_T_RAID1:
		return (meta->raid1_disks);
	case SII_T_RAID01:
		return (meta->raid0_disks * meta->raid1_disks);
	case SII_T_SPARE:
	case SII_T_JBOD:
		return (1);
	}
	return (0);
}