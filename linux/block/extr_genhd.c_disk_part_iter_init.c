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
struct gendisk {int /*<<< orphan*/  part_tbl; } ;
struct disk_part_tbl {int len; } ;
struct disk_part_iter {int idx; unsigned int flags; int /*<<< orphan*/ * part; struct gendisk* disk; } ;

/* Variables and functions */
 unsigned int DISK_PITER_INCL_EMPTY_PART0 ; 
 unsigned int DISK_PITER_INCL_PART0 ; 
 unsigned int DISK_PITER_REVERSE ; 
 struct disk_part_tbl* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

void disk_part_iter_init(struct disk_part_iter *piter, struct gendisk *disk,
			  unsigned int flags)
{
	struct disk_part_tbl *ptbl;

	rcu_read_lock();
	ptbl = rcu_dereference(disk->part_tbl);

	piter->disk = disk;
	piter->part = NULL;

	if (flags & DISK_PITER_REVERSE)
		piter->idx = ptbl->len - 1;
	else if (flags & (DISK_PITER_INCL_PART0 | DISK_PITER_INCL_EMPTY_PART0))
		piter->idx = 0;
	else
		piter->idx = 1;

	piter->flags = flags;

	rcu_read_unlock();
}