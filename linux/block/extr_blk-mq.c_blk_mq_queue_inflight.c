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

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_queue_tag_busy_iter (struct request_queue*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  blk_mq_rq_inflight ; 

bool blk_mq_queue_inflight(struct request_queue *q)
{
	bool busy = false;

	blk_mq_queue_tag_busy_iter(q, blk_mq_rq_inflight, &busy);
	return busy;
}