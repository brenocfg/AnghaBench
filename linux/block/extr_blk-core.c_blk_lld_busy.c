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
struct request_queue {TYPE_1__* mq_ops; } ;
struct TYPE_2__ {int (* busy ) (struct request_queue*) ;} ;

/* Variables and functions */
 scalar_t__ queue_is_mq (struct request_queue*) ; 
 int stub1 (struct request_queue*) ; 

int blk_lld_busy(struct request_queue *q)
{
	if (queue_is_mq(q) && q->mq_ops->busy)
		return q->mq_ops->busy(q);

	return 0;
}