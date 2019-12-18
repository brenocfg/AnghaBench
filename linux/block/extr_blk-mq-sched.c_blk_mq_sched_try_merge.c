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
struct request {int dummy; } ;
struct bio {int dummy; } ;

/* Variables and functions */
#define  ELEVATOR_BACK_MERGE 130 
#define  ELEVATOR_DISCARD_MERGE 129 
#define  ELEVATOR_FRONT_MERGE 128 
 struct request* attempt_back_merge (struct request_queue*,struct request*) ; 
 struct request* attempt_front_merge (struct request_queue*,struct request*) ; 
 int /*<<< orphan*/  bio_attempt_back_merge (struct request*,struct bio*,unsigned int) ; 
 int bio_attempt_discard_merge (struct request_queue*,struct request*,struct bio*) ; 
 int /*<<< orphan*/  bio_attempt_front_merge (struct request*,struct bio*,unsigned int) ; 
 int /*<<< orphan*/  blk_mq_sched_allow_merge (struct request_queue*,struct request*,struct bio*) ; 
 int elv_merge (struct request_queue*,struct request**,struct bio*) ; 
 int /*<<< orphan*/  elv_merged_request (struct request_queue*,struct request*,int const) ; 

bool blk_mq_sched_try_merge(struct request_queue *q, struct bio *bio,
		unsigned int nr_segs, struct request **merged_request)
{
	struct request *rq;

	switch (elv_merge(q, &rq, bio)) {
	case ELEVATOR_BACK_MERGE:
		if (!blk_mq_sched_allow_merge(q, rq, bio))
			return false;
		if (!bio_attempt_back_merge(rq, bio, nr_segs))
			return false;
		*merged_request = attempt_back_merge(q, rq);
		if (!*merged_request)
			elv_merged_request(q, rq, ELEVATOR_BACK_MERGE);
		return true;
	case ELEVATOR_FRONT_MERGE:
		if (!blk_mq_sched_allow_merge(q, rq, bio))
			return false;
		if (!bio_attempt_front_merge(rq, bio, nr_segs))
			return false;
		*merged_request = attempt_front_merge(q, rq);
		if (!*merged_request)
			elv_merged_request(q, rq, ELEVATOR_FRONT_MERGE);
		return true;
	case ELEVATOR_DISCARD_MERGE:
		return bio_attempt_discard_merge(q, rq, bio);
	default:
		return false;
	}
}