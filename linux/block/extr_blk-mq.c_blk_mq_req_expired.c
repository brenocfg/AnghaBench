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
struct request {int rq_flags; int /*<<< orphan*/  deadline; } ;

/* Variables and functions */
 scalar_t__ MQ_RQ_IN_FLIGHT ; 
 unsigned long READ_ONCE (int /*<<< orphan*/ ) ; 
 int RQF_TIMED_OUT ; 
 scalar_t__ blk_mq_rq_state (struct request*) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 
 scalar_t__ time_after_eq (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool blk_mq_req_expired(struct request *rq, unsigned long *next)
{
	unsigned long deadline;

	if (blk_mq_rq_state(rq) != MQ_RQ_IN_FLIGHT)
		return false;
	if (rq->rq_flags & RQF_TIMED_OUT)
		return false;

	deadline = READ_ONCE(rq->deadline);
	if (time_after_eq(jiffies, deadline))
		return true;

	if (*next == 0)
		*next = deadline;
	else if (time_after(*next, deadline))
		*next = deadline;
	return false;
}