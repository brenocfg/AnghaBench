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
struct request_queue {TYPE_1__* poll_stat; } ;
struct request {int dummy; } ;
struct blk_mq_hw_ctx {int dummy; } ;
struct TYPE_2__ {int mean; scalar_t__ nr_samples; } ;

/* Variables and functions */
 int blk_mq_poll_stats_bkt (struct request*) ; 
 int /*<<< orphan*/  blk_poll_stats_enable (struct request_queue*) ; 

__attribute__((used)) static unsigned long blk_mq_poll_nsecs(struct request_queue *q,
				       struct blk_mq_hw_ctx *hctx,
				       struct request *rq)
{
	unsigned long ret = 0;
	int bucket;

	/*
	 * If stats collection isn't on, don't sleep but turn it on for
	 * future users
	 */
	if (!blk_poll_stats_enable(q))
		return 0;

	/*
	 * As an optimistic guess, use half of the mean service time
	 * for this type of request. We can (and should) make this smarter.
	 * For instance, if the completion latencies are tight, we can
	 * get closer than just half the mean. This is especially
	 * important on devices where the completion latencies are longer
	 * than ~10 usec. We do use the stats for the relevant IO size
	 * if available which does lead to better estimates.
	 */
	bucket = blk_mq_poll_stats_bkt(rq);
	if (bucket < 0)
		return ret;

	if (q->poll_stat[bucket].nr_samples)
		ret = (q->poll_stat[bucket].mean + 1) / 2;

	return ret;
}