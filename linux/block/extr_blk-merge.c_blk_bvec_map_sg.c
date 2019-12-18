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
struct scatterlist {int dummy; } ;
struct request_queue {int dummy; } ;
struct page {int dummy; } ;
struct bio_vec {unsigned int bv_len; unsigned int bv_offset; struct page* bv_page; } ;

/* Variables and functions */
 unsigned int PAGE_MASK ; 
 unsigned int PAGE_SHIFT ; 
 struct scatterlist* blk_next_sg (struct scatterlist**,struct scatterlist*) ; 
 int /*<<< orphan*/  get_max_segment_size (struct request_queue*,unsigned int) ; 
 unsigned int min (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  sg_set_page (struct scatterlist*,struct page*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned blk_bvec_map_sg(struct request_queue *q,
		struct bio_vec *bvec, struct scatterlist *sglist,
		struct scatterlist **sg)
{
	unsigned nbytes = bvec->bv_len;
	unsigned nsegs = 0, total = 0;

	while (nbytes > 0) {
		unsigned offset = bvec->bv_offset + total;
		unsigned len = min(get_max_segment_size(q, offset), nbytes);
		struct page *page = bvec->bv_page;

		/*
		 * Unfortunately a fair number of drivers barf on scatterlists
		 * that have an offset larger than PAGE_SIZE, despite other
		 * subsystems dealing with that invariant just fine.  For now
		 * stick to the legacy format where we never present those from
		 * the block layer, but the code below should be removed once
		 * these offenders (mostly MMC/SD drivers) are fixed.
		 */
		page += (offset >> PAGE_SHIFT);
		offset &= ~PAGE_MASK;

		*sg = blk_next_sg(sg, sglist);
		sg_set_page(*sg, page, len, offset);

		total += len;
		nbytes -= len;
		nsegs++;
	}

	return nsegs;
}