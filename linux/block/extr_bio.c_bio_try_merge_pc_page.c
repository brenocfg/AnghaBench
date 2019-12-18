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
struct request_queue {int dummy; } ;
struct page {int dummy; } ;
struct bio_vec {unsigned int bv_offset; unsigned int bv_len; struct page* bv_page; } ;
struct bio {int bi_vcnt; struct bio_vec* bi_io_vec; } ;
typedef  unsigned long phys_addr_t ;

/* Variables and functions */
 int __bio_try_merge_page (struct bio*,struct page*,unsigned int,unsigned int,int*) ; 
 unsigned int page_to_phys (struct page*) ; 
 unsigned int queue_max_segment_size (struct request_queue*) ; 
 unsigned long queue_segment_boundary (struct request_queue*) ; 

__attribute__((used)) static bool bio_try_merge_pc_page(struct request_queue *q, struct bio *bio,
		struct page *page, unsigned len, unsigned offset,
		bool *same_page)
{
	struct bio_vec *bv = &bio->bi_io_vec[bio->bi_vcnt - 1];
	unsigned long mask = queue_segment_boundary(q);
	phys_addr_t addr1 = page_to_phys(bv->bv_page) + bv->bv_offset;
	phys_addr_t addr2 = page_to_phys(page) + offset + len - 1;

	if ((addr1 | mask) != (addr2 | mask))
		return false;
	if (bv->bv_len + len > queue_max_segment_size(q))
		return false;
	return __bio_try_merge_page(bio, page, len, offset, same_page);
}