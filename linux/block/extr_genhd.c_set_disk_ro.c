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
struct hd_struct {int policy; } ;
struct TYPE_2__ {int policy; } ;
struct gendisk {TYPE_1__ part0; } ;
struct disk_part_iter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DISK_PITER_INCL_EMPTY ; 
 int /*<<< orphan*/  disk_part_iter_exit (struct disk_part_iter*) ; 
 int /*<<< orphan*/  disk_part_iter_init (struct disk_part_iter*,struct gendisk*,int /*<<< orphan*/ ) ; 
 struct hd_struct* disk_part_iter_next (struct disk_part_iter*) ; 
 int /*<<< orphan*/  set_disk_ro_uevent (struct gendisk*,int) ; 

void set_disk_ro(struct gendisk *disk, int flag)
{
	struct disk_part_iter piter;
	struct hd_struct *part;

	if (disk->part0.policy != flag) {
		set_disk_ro_uevent(disk, flag);
		disk->part0.policy = flag;
	}

	disk_part_iter_init(&piter, disk, DISK_PITER_INCL_EMPTY);
	while ((part = disk_part_iter_next(&piter)))
		part->policy = flag;
	disk_part_iter_exit(&piter);
}