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
struct carm_host {unsigned int wait_q_prod; unsigned int wait_q_cons; struct request_queue** wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int CARM_MAX_WAIT_Q ; 
 int /*<<< orphan*/  VPRINTK (char*,struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_stop_hw_queues (struct request_queue*) ; 

__attribute__((used)) static inline void carm_push_q (struct carm_host *host, struct request_queue *q)
{
	unsigned int idx = host->wait_q_prod % CARM_MAX_WAIT_Q;

	blk_mq_stop_hw_queues(q);
	VPRINTK("STOPPED QUEUE %p\n", q);

	host->wait_q[idx] = q;
	host->wait_q_prod++;
	BUG_ON(host->wait_q_prod == host->wait_q_cons); /* overrun */
}