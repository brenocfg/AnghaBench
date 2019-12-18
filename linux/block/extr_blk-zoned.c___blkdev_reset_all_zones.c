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
struct block_device {int dummy; } ;
struct bio {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int /*<<< orphan*/  REQ_OP_ZONE_RESET_ALL ; 
 struct bio* bio_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_put (struct bio*) ; 
 int /*<<< orphan*/  bio_set_dev (struct bio*,struct block_device*) ; 
 int /*<<< orphan*/  bio_set_op_attrs (struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int submit_bio_wait (struct bio*) ; 

__attribute__((used)) static int __blkdev_reset_all_zones(struct block_device *bdev, gfp_t gfp_mask)
{
	struct bio *bio = bio_alloc(gfp_mask, 0);
	int ret;

	/* across the zones operations, don't need any sectors */
	bio_set_dev(bio, bdev);
	bio_set_op_attrs(bio, REQ_OP_ZONE_RESET_ALL, 0);

	ret = submit_bio_wait(bio);
	bio_put(bio);

	return ret;
}