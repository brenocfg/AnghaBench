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
struct request_queue {int dummy; } ;
struct block_device {TYPE_1__* bd_part; } ;
struct blk_plug {int dummy; } ;
struct TYPE_4__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_2__ bi_iter; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {scalar_t__ nr_sects; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  REQ_OP_ZONE_RESET ; 
 int __blkdev_reset_all_zones (struct block_device*,int /*<<< orphan*/ ) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 scalar_t__ bdev_read_only (struct block_device*) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_finish_plug (struct blk_plug*) ; 
 struct bio* blk_next_bio (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_is_zoned (struct request_queue*) ; 
 scalar_t__ blk_queue_zone_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  blk_start_plug (struct blk_plug*) ; 
 scalar_t__ blkdev_allow_reset_all_zones (struct block_device*,scalar_t__) ; 
 int /*<<< orphan*/  cond_resched () ; 
 int submit_bio_wait (struct bio*) ; 

int blkdev_reset_zones(struct block_device *bdev,
		       sector_t sector, sector_t nr_sectors,
		       gfp_t gfp_mask)
{
	struct request_queue *q = bdev_get_queue(bdev);
	sector_t zone_sectors;
	sector_t end_sector = sector + nr_sectors;
	struct bio *bio = NULL;
	struct blk_plug plug;
	int ret;

	if (!blk_queue_is_zoned(q))
		return -EOPNOTSUPP;

	if (bdev_read_only(bdev))
		return -EPERM;

	if (!nr_sectors || end_sector > bdev->bd_part->nr_sects)
		/* Out of range */
		return -EINVAL;

	if (blkdev_allow_reset_all_zones(bdev, nr_sectors))
		return  __blkdev_reset_all_zones(bdev, gfp_mask);

	/* Check alignment (handle eventual smaller last zone) */
	zone_sectors = blk_queue_zone_sectors(q);
	if (sector & (zone_sectors - 1))
		return -EINVAL;

	if ((nr_sectors & (zone_sectors - 1)) &&
	    end_sector != bdev->bd_part->nr_sects)
		return -EINVAL;

	blk_start_plug(&plug);
	while (sector < end_sector) {

		bio = blk_next_bio(bio, 0, gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio_set_op_attrs(bio, REQ_OP_ZONE_RESET, 0);

		sector += zone_sectors;

		/* This may take a while, so be nice to others */
		cond_resched();

	}

	ret = submit_bio_wait(bio);
	bio_put(bio);

	blk_finish_plug(&plug);

	return ret;
}