#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct gendisk {int first_minor; int /*<<< orphan*/  disk_name; int /*<<< orphan*/  flags; struct brd_device* private_data; int /*<<< orphan*/ * fops; int /*<<< orphan*/  major; } ;
struct brd_device {int brd_number; TYPE_2__* brd_queue; struct gendisk* brd_disk; int /*<<< orphan*/  brd_pages; int /*<<< orphan*/  brd_lock; } ;
struct TYPE_10__ {TYPE_1__* backing_dev_info; } ;
struct TYPE_9__ {int /*<<< orphan*/  capabilities; } ;

/* Variables and functions */
 int /*<<< orphan*/  BDI_CAP_SYNCHRONOUS_IO ; 
 int /*<<< orphan*/  GENHD_FL_EXT_DEVT ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_ADD_RANDOM ; 
 int /*<<< orphan*/  QUEUE_FLAG_NONROT ; 
 int /*<<< orphan*/  RAMDISK_MAJOR ; 
 struct gendisk* alloc_disk (int) ; 
 TYPE_2__* blk_alloc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_cleanup_queue (TYPE_2__*) ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  blk_queue_make_request (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (TYPE_2__*,int) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brd_fops ; 
 int /*<<< orphan*/  brd_make_request ; 
 int /*<<< orphan*/  kfree (struct brd_device*) ; 
 struct brd_device* kzalloc (int,int /*<<< orphan*/ ) ; 
 int max_part ; 
 int rd_size ; 
 int /*<<< orphan*/  set_capacity (struct gendisk*,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sprintf (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static struct brd_device *brd_alloc(int i)
{
	struct brd_device *brd;
	struct gendisk *disk;

	brd = kzalloc(sizeof(*brd), GFP_KERNEL);
	if (!brd)
		goto out;
	brd->brd_number		= i;
	spin_lock_init(&brd->brd_lock);
	INIT_RADIX_TREE(&brd->brd_pages, GFP_ATOMIC);

	brd->brd_queue = blk_alloc_queue(GFP_KERNEL);
	if (!brd->brd_queue)
		goto out_free_dev;

	blk_queue_make_request(brd->brd_queue, brd_make_request);
	blk_queue_max_hw_sectors(brd->brd_queue, 1024);

	/* This is so fdisk will align partitions on 4k, because of
	 * direct_access API needing 4k alignment, returning a PFN
	 * (This is only a problem on very small devices <= 4M,
	 *  otherwise fdisk will align on 1M. Regardless this call
	 *  is harmless)
	 */
	blk_queue_physical_block_size(brd->brd_queue, PAGE_SIZE);
	disk = brd->brd_disk = alloc_disk(max_part);
	if (!disk)
		goto out_free_queue;
	disk->major		= RAMDISK_MAJOR;
	disk->first_minor	= i * max_part;
	disk->fops		= &brd_fops;
	disk->private_data	= brd;
	disk->flags		= GENHD_FL_EXT_DEVT;
	sprintf(disk->disk_name, "ram%d", i);
	set_capacity(disk, rd_size * 2);
	brd->brd_queue->backing_dev_info->capabilities |= BDI_CAP_SYNCHRONOUS_IO;

	/* Tell the block layer that this is not a rotational device */
	blk_queue_flag_set(QUEUE_FLAG_NONROT, brd->brd_queue);
	blk_queue_flag_clear(QUEUE_FLAG_ADD_RANDOM, brd->brd_queue);

	return brd;

out_free_queue:
	blk_cleanup_queue(brd->brd_queue);
out_free_dev:
	kfree(brd);
out:
	return NULL;
}