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
struct page {int dummy; } ;
struct block_device {int dummy; } ;
struct TYPE_4__ {int bi_sector; unsigned int bi_size; } ;
struct bio {int bi_vcnt; TYPE_2__ bi_iter; TYPE_1__* bi_io_vec; } ;
typedef  int sector_t ;
typedef  int /*<<< orphan*/  gfp_t ;
struct TYPE_3__ {int bv_len; scalar_t__ bv_offset; struct page* bv_page; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENXIO ; 
 int EOPNOTSUPP ; 
 int EPERM ; 
 int /*<<< orphan*/  REQ_OP_WRITE_SAME ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int bdev_logical_block_size (struct block_device*) ; 
 scalar_t__ bdev_read_only (struct block_device*) ; 
 int /*<<< orphan*/  bdev_write_same (struct block_device*) ; 
 unsigned int bio_allowed_max_sectors (struct request_queue*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bio* blk_next_bio (struct bio*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cond_resched () ; 

__attribute__((used)) static int __blkdev_issue_write_same(struct block_device *bdev, sector_t sector,
		sector_t nr_sects, gfp_t gfp_mask, struct page *page,
		struct bio **biop)
{
	struct request_queue *q = bdev_get_queue(bdev);
	unsigned int max_write_same_sectors;
	struct bio *bio = *biop;
	sector_t bs_mask;

	if (!q)
		return -ENXIO;

	if (bdev_read_only(bdev))
		return -EPERM;

	bs_mask = (bdev_logical_block_size(bdev) >> 9) - 1;
	if ((sector | nr_sects) & bs_mask)
		return -EINVAL;

	if (!bdev_write_same(bdev))
		return -EOPNOTSUPP;

	/* Ensure that max_write_same_sectors doesn't overflow bi_size */
	max_write_same_sectors = bio_allowed_max_sectors(q);

	while (nr_sects) {
		bio = blk_next_bio(bio, 1, gfp_mask);
		bio->bi_iter.bi_sector = sector;
		bio_set_dev(bio, bdev);
		bio->bi_vcnt = 1;
		bio->bi_io_vec->bv_page = page;
		bio->bi_io_vec->bv_offset = 0;
		bio->bi_io_vec->bv_len = bdev_logical_block_size(bdev);
		bio_set_op_attrs(bio, REQ_OP_WRITE_SAME, 0);

		if (nr_sects > max_write_same_sectors) {
			bio->bi_iter.bi_size = max_write_same_sectors << 9;
			nr_sects -= max_write_same_sectors;
			sector += max_write_same_sectors;
		} else {
			bio->bi_iter.bi_size = nr_sects << 9;
			nr_sects = 0;
		}
		cond_resched();
	}

	*biop = bio;
	return 0;
}