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
struct request {int nr_phys_segments; int /*<<< orphan*/  bio; } ;

/* Variables and functions */
 int blk_integrity_merge_rq (struct request_queue*,struct request*,struct request*) ; 
 scalar_t__ blk_rq_get_max_sectors (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 
 int queue_max_segments (struct request_queue*) ; 
 scalar_t__ req_gap_back_merge (struct request*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ll_merge_requests_fn(struct request_queue *q, struct request *req,
				struct request *next)
{
	int total_phys_segments;

	if (req_gap_back_merge(req, next->bio))
		return 0;

	/*
	 * Will it become too large?
	 */
	if ((blk_rq_sectors(req) + blk_rq_sectors(next)) >
	    blk_rq_get_max_sectors(req, blk_rq_pos(req)))
		return 0;

	total_phys_segments = req->nr_phys_segments + next->nr_phys_segments;
	if (total_phys_segments > queue_max_segments(q))
		return 0;

	if (blk_integrity_merge_rq(q, req, next) == false)
		return 0;

	/* Merge is OK... */
	req->nr_phys_segments = total_phys_segments;
	return 1;
}