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
struct request {int dummy; } ;
typedef  enum elv_merge { ____Placeholder_elv_merge } elv_merge ;

/* Variables and functions */
 int ELEVATOR_BACK_MERGE ; 
 int ELEVATOR_DISCARD_MERGE ; 
 int ELEVATOR_NO_MERGE ; 
 scalar_t__ blk_discard_mergable (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 

__attribute__((used)) static enum elv_merge blk_try_req_merge(struct request *req,
					struct request *next)
{
	if (blk_discard_mergable(req))
		return ELEVATOR_DISCARD_MERGE;
	else if (blk_rq_pos(req) + blk_rq_sectors(req) == blk_rq_pos(next))
		return ELEVATOR_BACK_MERGE;

	return ELEVATOR_NO_MERGE;
}