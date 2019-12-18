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
struct request_queue {int /*<<< orphan*/  mq_freeze_wq; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_DYING ; 
 int /*<<< orphan*/  blk_freeze_queue_start (struct request_queue*) ; 
 int /*<<< orphan*/  blk_mq_wake_waiters (struct request_queue*) ; 
 int /*<<< orphan*/  blk_queue_flag_set (int /*<<< orphan*/ ,struct request_queue*) ; 
 scalar_t__ queue_is_mq (struct request_queue*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void blk_set_queue_dying(struct request_queue *q)
{
	blk_queue_flag_set(QUEUE_FLAG_DYING, q);

	/*
	 * When queue DYING flag is set, we need to block new req
	 * entering queue, so we call blk_freeze_queue_start() to
	 * prevent I/O from crossing blk_queue_enter().
	 */
	blk_freeze_queue_start(q);

	if (queue_is_mq(q))
		blk_mq_wake_waiters(q);

	/* Make blk_queue_enter() reexamine the DYING flag. */
	wake_up_all(&q->mq_freeze_wq);
}