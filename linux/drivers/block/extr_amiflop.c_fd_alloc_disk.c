#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct gendisk {int /*<<< orphan*/ * queue; } ;
struct TYPE_4__ {TYPE_1__* type; int /*<<< orphan*/  tag_set; int /*<<< orphan*/  trackbuf; } ;
struct TYPE_3__ {int /*<<< orphan*/  code; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLK_MQ_F_SHOULD_MERGE ; 
 int /*<<< orphan*/  FD_NODRIVE ; 
 int FLOPPY_MAX_SECTORS ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (int /*<<< orphan*/ *) ; 
 struct gendisk* alloc_disk (int) ; 
 int /*<<< orphan*/  amiflop_mq_ops ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  blk_mq_free_tag_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * blk_mq_init_sq_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  put_disk (struct gendisk*) ; 
 TYPE_2__* unit ; 

__attribute__((used)) static struct gendisk *fd_alloc_disk(int drive)
{
	struct gendisk *disk;

	disk = alloc_disk(1);
	if (!disk)
		goto out;

	disk->queue = blk_mq_init_sq_queue(&unit[drive].tag_set, &amiflop_mq_ops,
						2, BLK_MQ_F_SHOULD_MERGE);
	if (IS_ERR(disk->queue)) {
		disk->queue = NULL;
		goto out_put_disk;
	}

	unit[drive].trackbuf = kmalloc(FLOPPY_MAX_SECTORS * 512, GFP_KERNEL);
	if (!unit[drive].trackbuf)
		goto out_cleanup_queue;

	return disk;

out_cleanup_queue:
	blk_cleanup_queue(disk->queue);
	disk->queue = NULL;
	blk_mq_free_tag_set(&unit[drive].tag_set);
out_put_disk:
	put_disk(disk);
out:
	unit[drive].type->code = FD_NODRIVE;
	return NULL;
}