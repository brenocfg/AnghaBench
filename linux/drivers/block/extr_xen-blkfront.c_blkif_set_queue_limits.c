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
struct TYPE_2__ {int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  discard_granularity; } ;
struct request_queue {TYPE_1__ limits; } ;
struct gendisk {int dummy; } ;
struct blkfront_info {int /*<<< orphan*/  physical_sector_size; int /*<<< orphan*/  sector_size; scalar_t__ feature_secdiscard; int /*<<< orphan*/  discard_alignment; int /*<<< orphan*/  discard_granularity; scalar_t__ feature_discard; scalar_t__ max_indirect_segments; struct gendisk* gd; struct request_queue* rq; } ;

/* Variables and functions */
 unsigned int BLKIF_MAX_SEGMENTS_PER_REQUEST ; 
 unsigned int GRANTS_PER_PSEG ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  QUEUE_FLAG_DISCARD ; 
 int /*<<< orphan*/  QUEUE_FLAG_SECERASE ; 
 int /*<<< orphan*/  QUEUE_FLAG_VIRT ; 
 unsigned int XEN_PAGE_SIZE ; 
 int /*<<< orphan*/  blk_queue_dma_alignment (struct request_queue*,int) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_logical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_discard_sectors (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_max_hw_sectors (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_max_segment_size (struct request_queue*,scalar_t__) ; 
 int /*<<< orphan*/  blk_queue_max_segments (struct request_queue*,unsigned int) ; 
 int /*<<< orphan*/  blk_queue_physical_block_size (struct request_queue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_queue_segment_boundary (struct request_queue*,scalar_t__) ; 
 int /*<<< orphan*/  get_capacity (struct gendisk*) ; 

__attribute__((used)) static void blkif_set_queue_limits(struct blkfront_info *info)
{
	struct request_queue *rq = info->rq;
	struct gendisk *gd = info->gd;
	unsigned int segments = info->max_indirect_segments ? :
				BLKIF_MAX_SEGMENTS_PER_REQUEST;

	blk_queue_flag_set(QUEUE_FLAG_VIRT, rq);

	if (info->feature_discard) {
		blk_queue_flag_set(QUEUE_FLAG_DISCARD, rq);
		blk_queue_max_discard_sectors(rq, get_capacity(gd));
		rq->limits.discard_granularity = info->discard_granularity;
		rq->limits.discard_alignment = info->discard_alignment;
		if (info->feature_secdiscard)
			blk_queue_flag_set(QUEUE_FLAG_SECERASE, rq);
	}

	/* Hard sector size and max sectors impersonate the equiv. hardware. */
	blk_queue_logical_block_size(rq, info->sector_size);
	blk_queue_physical_block_size(rq, info->physical_sector_size);
	blk_queue_max_hw_sectors(rq, (segments * XEN_PAGE_SIZE) / 512);

	/* Each segment in a request is up to an aligned page in size. */
	blk_queue_segment_boundary(rq, PAGE_SIZE - 1);
	blk_queue_max_segment_size(rq, PAGE_SIZE);

	/* Ensure a merged request will fit in a single I/O ring slot. */
	blk_queue_max_segments(rq, segments / GRANTS_PER_PSEG);

	/* Make sure buffer addresses are sector-aligned. */
	blk_queue_dma_alignment(rq, 511);
}