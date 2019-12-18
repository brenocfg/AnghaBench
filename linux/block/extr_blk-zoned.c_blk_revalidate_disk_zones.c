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
struct request_queue {unsigned int nr_zones; int /*<<< orphan*/  seq_zones_bitmap; int /*<<< orphan*/  seq_zones_wlock; int /*<<< orphan*/  node; } ;
struct gendisk {int /*<<< orphan*/  disk_name; struct request_queue* queue; } ;
struct blk_zone {scalar_t__ type; } ;
typedef  unsigned int sector_t ;

/* Variables and functions */
 scalar_t__ BLK_ZONE_TYPE_CONVENTIONAL ; 
 int EIO ; 
 int ENOMEM ; 
 scalar_t__ WARN_ON (int) ; 
 unsigned int __blkdev_nr_zones (struct request_queue*,int /*<<< orphan*/ ) ; 
 unsigned long* blk_alloc_zone_bitmap (int /*<<< orphan*/ ,unsigned int) ; 
 struct blk_zone* blk_alloc_zones (unsigned int*) ; 
 int /*<<< orphan*/  blk_mq_freeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_unfreeze_queue (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_free_zone_bitmaps (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_is_zoned (struct request_queue*) ; 
 unsigned int blk_queue_zone_sectors (struct request_queue*) ; 
 int blk_report_zones (struct gendisk*,unsigned int,struct blk_zone*,unsigned int*) ; 
 int /*<<< orphan*/  get_capacity (struct gendisk*) ; 
 int /*<<< orphan*/  kfree (unsigned long*) ; 
 int /*<<< orphan*/  kvfree (struct blk_zone*) ; 
 int /*<<< orphan*/  memalloc_noio_restore (unsigned int) ; 
 unsigned int memalloc_noio_save () ; 
 unsigned int min (unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_is_mq (struct request_queue*) ; 
 int /*<<< orphan*/  set_bit (unsigned int,unsigned long*) ; 
 int /*<<< orphan*/  swap (int /*<<< orphan*/ ,unsigned long*) ; 

int blk_revalidate_disk_zones(struct gendisk *disk)
{
	struct request_queue *q = disk->queue;
	unsigned int nr_zones = __blkdev_nr_zones(q, get_capacity(disk));
	unsigned long *seq_zones_wlock = NULL, *seq_zones_bitmap = NULL;
	unsigned int i, rep_nr_zones = 0, z = 0, nrz;
	struct blk_zone *zones = NULL;
	unsigned int noio_flag;
	sector_t sector = 0;
	int ret = 0;

	/*
	 * BIO based queues do not use a scheduler so only q->nr_zones
	 * needs to be updated so that the sysfs exposed value is correct.
	 */
	if (!queue_is_mq(q)) {
		q->nr_zones = nr_zones;
		return 0;
	}

	/*
	 * Ensure that all memory allocations in this context are done as
	 * if GFP_NOIO was specified.
	 */
	noio_flag = memalloc_noio_save();

	if (!blk_queue_is_zoned(q) || !nr_zones) {
		nr_zones = 0;
		goto update;
	}

	/* Allocate bitmaps */
	ret = -ENOMEM;
	seq_zones_wlock = blk_alloc_zone_bitmap(q->node, nr_zones);
	if (!seq_zones_wlock)
		goto out;
	seq_zones_bitmap = blk_alloc_zone_bitmap(q->node, nr_zones);
	if (!seq_zones_bitmap)
		goto out;

	/* Get zone information and initialize seq_zones_bitmap */
	rep_nr_zones = nr_zones;
	zones = blk_alloc_zones(&rep_nr_zones);
	if (!zones)
		goto out;

	while (z < nr_zones) {
		nrz = min(nr_zones - z, rep_nr_zones);
		ret = blk_report_zones(disk, sector, zones, &nrz);
		if (ret)
			goto out;
		if (!nrz)
			break;
		for (i = 0; i < nrz; i++) {
			if (zones[i].type != BLK_ZONE_TYPE_CONVENTIONAL)
				set_bit(z, seq_zones_bitmap);
			z++;
		}
		sector += nrz * blk_queue_zone_sectors(q);
	}

	if (WARN_ON(z != nr_zones)) {
		ret = -EIO;
		goto out;
	}

update:
	/*
	 * Install the new bitmaps, making sure the queue is stopped and
	 * all I/Os are completed (i.e. a scheduler is not referencing the
	 * bitmaps).
	 */
	blk_mq_freeze_queue(q);
	q->nr_zones = nr_zones;
	swap(q->seq_zones_wlock, seq_zones_wlock);
	swap(q->seq_zones_bitmap, seq_zones_bitmap);
	blk_mq_unfreeze_queue(q);

out:
	memalloc_noio_restore(noio_flag);

	kvfree(zones);
	kfree(seq_zones_wlock);
	kfree(seq_zones_bitmap);

	if (ret) {
		pr_warn("%s: failed to revalidate zones\n", disk->disk_name);
		blk_mq_freeze_queue(q);
		blk_queue_free_zone_bitmaps(q);
		blk_mq_unfreeze_queue(q);
	}

	return ret;
}