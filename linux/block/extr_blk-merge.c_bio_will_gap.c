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
struct request {struct bio* bio; } ;
struct bio_vec {int bv_offset; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int __bvec_gap_to_prev (struct request_queue*,struct bio_vec*,int) ; 
 int /*<<< orphan*/  bio_get_first_bvec (struct bio*,struct bio_vec*) ; 
 int /*<<< orphan*/  bio_get_last_bvec (struct bio*,struct bio_vec*) ; 
 int /*<<< orphan*/  bio_has_data (struct bio*) ; 
 scalar_t__ biovec_phys_mergeable (struct request_queue*,struct bio_vec*,struct bio_vec*) ; 
 int queue_virt_boundary (struct request_queue*) ; 

__attribute__((used)) static inline bool bio_will_gap(struct request_queue *q,
		struct request *prev_rq, struct bio *prev, struct bio *next)
{
	struct bio_vec pb, nb;

	if (!bio_has_data(prev) || !queue_virt_boundary(q))
		return false;

	/*
	 * Don't merge if the 1st bio starts with non-zero offset, otherwise it
	 * is quite difficult to respect the sg gap limit.  We work hard to
	 * merge a huge number of small single bios in case of mkfs.
	 */
	if (prev_rq)
		bio_get_first_bvec(prev_rq->bio, &pb);
	else
		bio_get_first_bvec(prev, &pb);
	if (pb.bv_offset & queue_virt_boundary(q))
		return true;

	/*
	 * We don't need to worry about the situation that the merged segment
	 * ends in unaligned virt boundary:
	 *
	 * - if 'pb' ends aligned, the merged segment ends aligned
	 * - if 'pb' ends unaligned, the next bio must include
	 *   one single bvec of 'nb', otherwise the 'nb' can't
	 *   merge with 'pb'
	 */
	bio_get_last_bvec(prev, &pb);
	bio_get_first_bvec(next, &nb);
	if (biovec_phys_mergeable(q, &pb, &nb))
		return false;
	return __bvec_gap_to_prev(q, &pb, nb.bv_offset);
}