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
typedef  int /*<<< orphan*/  u64 ;
struct request {int rq_flags; int internal_tag; int /*<<< orphan*/  (* end_io ) (struct request*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  q; } ;
typedef  int /*<<< orphan*/  blk_status_t ;

/* Variables and functions */
 int RQF_STATS ; 
 int /*<<< orphan*/  blk_account_io_done (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_free_request (struct request*) ; 
 scalar_t__ blk_mq_need_time_stamp (struct request*) ; 
 int /*<<< orphan*/  blk_mq_poll_stats_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_mq_sched_completed_request (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  blk_stat_add (struct request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get_ns () ; 
 int /*<<< orphan*/  rq_qos_done (int /*<<< orphan*/ ,struct request*) ; 
 int /*<<< orphan*/  stub1 (struct request*,int /*<<< orphan*/ ) ; 

inline void __blk_mq_end_request(struct request *rq, blk_status_t error)
{
	u64 now = 0;

	if (blk_mq_need_time_stamp(rq))
		now = ktime_get_ns();

	if (rq->rq_flags & RQF_STATS) {
		blk_mq_poll_stats_start(rq->q);
		blk_stat_add(rq, now);
	}

	if (rq->internal_tag != -1)
		blk_mq_sched_completed_request(rq, now);

	blk_account_io_done(rq, now);

	if (rq->end_io) {
		rq_qos_done(rq->q, rq);
		rq->end_io(rq, error);
	} else {
		blk_mq_free_request(rq);
	}
}