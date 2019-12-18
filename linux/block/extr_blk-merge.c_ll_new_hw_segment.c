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
struct request {scalar_t__ nr_phys_segments; int /*<<< orphan*/  q; } ;
struct bio {int dummy; } ;

/* Variables and functions */
 int blk_integrity_merge_bio (int /*<<< orphan*/ ,struct request*,struct bio*) ; 
 scalar_t__ queue_max_segments (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  req_set_nomerge (int /*<<< orphan*/ ,struct request*) ; 

__attribute__((used)) static inline int ll_new_hw_segment(struct request *req, struct bio *bio,
		unsigned int nr_phys_segs)
{
	if (req->nr_phys_segments + nr_phys_segs > queue_max_segments(req->q))
		goto no_merge;

	if (blk_integrity_merge_bio(req->q, req, bio) == false)
		goto no_merge;

	/*
	 * This will form the start of a new hw segment.  Bump both
	 * counters.
	 */
	req->nr_phys_segments += nr_phys_segs;
	return 1;

no_merge:
	req_set_nomerge(req->q, req);
	return 0;
}