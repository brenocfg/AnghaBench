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
struct carm_host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VPRINTK (char*,struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_start_hw_queues (struct request_queue*) ; 
 struct request_queue* carm_pop_q (struct carm_host*) ; 

__attribute__((used)) static inline void carm_round_robin(struct carm_host *host)
{
	struct request_queue *q = carm_pop_q(host);
	if (q) {
		blk_mq_start_hw_queues(q);
		VPRINTK("STARTED QUEUE %p\n", q);
	}
}