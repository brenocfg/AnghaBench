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
struct sii_raid_conf {int type; int disk_number; int raid1_ident; int raid1_disks; int raid0_ident; int /*<<< orphan*/  timestamp; } ;

/* Variables and functions */
#define  SII_T_CONCAT 133 
#define  SII_T_JBOD 132 
#define  SII_T_RAID0 131 
#define  SII_T_RAID01 130 
#define  SII_T_RAID1 129 
#define  SII_T_RAID5 128 
 int SII_T_SPARE ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
sii_meta_disk_pos(struct sii_raid_conf *meta, struct sii_raid_conf *pdmeta)
{

	if (pdmeta->type == SII_T_SPARE)
		return (-3);

	if (memcmp(&meta->timestamp, &pdmeta->timestamp, 6) != 0)
		return (-1);

	switch (pdmeta->type) {
	case SII_T_RAID0:
	case SII_T_RAID1:
	case SII_T_RAID5:
	case SII_T_CONCAT:
		return (pdmeta->disk_number);
	case SII_T_RAID01:
		return (pdmeta->raid1_ident * pdmeta->raid1_disks +
		    pdmeta->raid0_ident);
	case SII_T_JBOD:
		return (0);
	}
	return (-1);
}