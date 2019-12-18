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
struct request {int dummy; } ;
struct TYPE_2__ {scalar_t__ bi_sector; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  enum elv_merge { ____Placeholder_elv_merge } elv_merge ;

/* Variables and functions */
 int ELEVATOR_BACK_MERGE ; 
 int ELEVATOR_DISCARD_MERGE ; 
 int ELEVATOR_FRONT_MERGE ; 
 int ELEVATOR_NO_MERGE ; 
 scalar_t__ bio_sectors (struct bio*) ; 
 scalar_t__ blk_discard_mergable (struct request*) ; 
 scalar_t__ blk_rq_pos (struct request*) ; 
 scalar_t__ blk_rq_sectors (struct request*) ; 

enum elv_merge blk_try_merge(struct request *rq, struct bio *bio)
{
	if (blk_discard_mergable(rq))
		return ELEVATOR_DISCARD_MERGE;
	else if (blk_rq_pos(rq) + blk_rq_sectors(rq) == bio->bi_iter.bi_sector)
		return ELEVATOR_BACK_MERGE;
	else if (blk_rq_pos(rq) - bio_sectors(bio) == bio->bi_iter.bi_sector)
		return ELEVATOR_FRONT_MERGE;
	return ELEVATOR_NO_MERGE;
}