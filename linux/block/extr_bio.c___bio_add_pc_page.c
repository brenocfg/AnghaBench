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
struct request_queue {int dummy; } ;
struct page {int dummy; } ;
struct bio_vec {unsigned int bv_len; unsigned int bv_offset; struct page* bv_page; } ;
struct TYPE_2__ {unsigned int bi_size; } ;
struct bio {int bi_vcnt; TYPE_1__ bi_iter; struct bio_vec* bi_io_vec; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_CLONED ; 
 int /*<<< orphan*/  bio_flagged (struct bio*,int /*<<< orphan*/ ) ; 
 scalar_t__ bio_full (struct bio*,unsigned int) ; 
 scalar_t__ bio_try_merge_pc_page (struct request_queue*,struct bio*,struct page*,unsigned int,unsigned int,int*) ; 
 scalar_t__ bvec_gap_to_prev (struct request_queue*,struct bio_vec*,unsigned int) ; 
 unsigned int queue_max_hw_sectors (struct request_queue*) ; 
 int queue_max_segments (struct request_queue*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __bio_add_pc_page(struct request_queue *q, struct bio *bio,
		struct page *page, unsigned int len, unsigned int offset,
		bool *same_page)
{
	struct bio_vec *bvec;

	/*
	 * cloned bio must not modify vec list
	 */
	if (unlikely(bio_flagged(bio, BIO_CLONED)))
		return 0;

	if (((bio->bi_iter.bi_size + len) >> 9) > queue_max_hw_sectors(q))
		return 0;

	if (bio->bi_vcnt > 0) {
		if (bio_try_merge_pc_page(q, bio, page, len, offset, same_page))
			return len;

		/*
		 * If the queue doesn't support SG gaps and adding this segment
		 * would create a gap, disallow it.
		 */
		bvec = &bio->bi_io_vec[bio->bi_vcnt - 1];
		if (bvec_gap_to_prev(q, bvec, offset))
			return 0;
	}

	if (bio_full(bio, len))
		return 0;

	if (bio->bi_vcnt >= queue_max_segments(q))
		return 0;

	bvec = &bio->bi_io_vec[bio->bi_vcnt];
	bvec->bv_page = page;
	bvec->bv_len = len;
	bvec->bv_offset = offset;
	bio->bi_vcnt++;
	bio->bi_iter.bi_size += len;
	return len;
}