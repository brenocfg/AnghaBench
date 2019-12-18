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
struct request_queue {scalar_t__ mq_freeze_depth; int /*<<< orphan*/  mq_freeze_lock; int /*<<< orphan*/  mq_freeze_wq; int /*<<< orphan*/  q_usage_counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_resurrect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

void blk_mq_unfreeze_queue(struct request_queue *q)
{
	mutex_lock(&q->mq_freeze_lock);
	q->mq_freeze_depth--;
	WARN_ON_ONCE(q->mq_freeze_depth < 0);
	if (!q->mq_freeze_depth) {
		percpu_ref_resurrect(&q->q_usage_counter);
		wake_up_all(&q->mq_freeze_wq);
	}
	mutex_unlock(&q->mq_freeze_lock);
}