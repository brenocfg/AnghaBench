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
struct bio_vec {unsigned int bv_len; unsigned int bv_offset; } ;

/* Variables and functions */
 int UINT_MAX ; 
 unsigned int get_max_segment_size (struct request_queue const*,unsigned int) ; 
 unsigned int min (unsigned int,unsigned int) ; 
 unsigned int queue_virt_boundary (struct request_queue const*) ; 

__attribute__((used)) static bool bvec_split_segs(const struct request_queue *q,
			    const struct bio_vec *bv, unsigned *nsegs,
			    unsigned *sectors, unsigned max_segs,
			    unsigned max_sectors)
{
	unsigned max_len = (min(max_sectors, UINT_MAX >> 9) - *sectors) << 9;
	unsigned len = min(bv->bv_len, max_len);
	unsigned total_len = 0;
	unsigned seg_size = 0;

	while (len && *nsegs < max_segs) {
		seg_size = get_max_segment_size(q, bv->bv_offset + total_len);
		seg_size = min(seg_size, len);

		(*nsegs)++;
		total_len += seg_size;
		len -= seg_size;

		if ((bv->bv_offset + total_len) & queue_virt_boundary(q))
			break;
	}

	*sectors += total_len >> 9;

	/* tell the caller to split the bvec if it is too big to fit */
	return len > 0 || bv->bv_len > max_len;
}