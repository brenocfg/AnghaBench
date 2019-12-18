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
struct request_queue {struct blk_mq_tag_set* tag_set; } ;
struct blk_mq_tag_set {int /*<<< orphan*/  nr_hw_queues; } ;

/* Variables and functions */
 int /*<<< orphan*/  blk_mq_del_queue_tag_set (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_exit_hw_queues (struct request_queue*,struct blk_mq_tag_set*,int /*<<< orphan*/ ) ; 

void blk_mq_exit_queue(struct request_queue *q)
{
	struct blk_mq_tag_set	*set = q->tag_set;

	blk_mq_del_queue_tag_set(q);
	blk_mq_exit_hw_queues(q, set, set->nr_hw_queues);
}