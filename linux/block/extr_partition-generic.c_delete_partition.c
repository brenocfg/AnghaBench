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
struct hd_struct {int /*<<< orphan*/  holder_dir; } ;
struct gendisk {int /*<<< orphan*/  part_tbl; } ;
struct disk_part_tbl {int len; int /*<<< orphan*/  last_lookup; int /*<<< orphan*/ * part; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_invalidate_devt (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hd_struct_kill (struct hd_struct*) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  part_devt (struct hd_struct*) ; 
 int /*<<< orphan*/  part_to_dev (struct hd_struct*) ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* rcu_dereference_protected (int /*<<< orphan*/ ,int) ; 

void delete_partition(struct gendisk *disk, int partno)
{
	struct disk_part_tbl *ptbl =
		rcu_dereference_protected(disk->part_tbl, 1);
	struct hd_struct *part;

	if (partno >= ptbl->len)
		return;

	part = rcu_dereference_protected(ptbl->part[partno], 1);
	if (!part)
		return;

	rcu_assign_pointer(ptbl->part[partno], NULL);
	rcu_assign_pointer(ptbl->last_lookup, NULL);
	kobject_put(part->holder_dir);
	device_del(part_to_dev(part));

	/*
	 * Remove gendisk pointer from idr so that it cannot be looked up
	 * while RCU period before freeing gendisk is running to prevent
	 * use-after-free issues. Note that the device number stays
	 * "in-use" until we really free the gendisk.
	 */
	blk_invalidate_devt(part_devt(part));
	hd_struct_kill(part);
}