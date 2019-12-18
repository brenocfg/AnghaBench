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
struct request_queue {TYPE_1__* stats; } ;
struct blk_stat_callback {int /*<<< orphan*/  timer; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  enable_accounting; int /*<<< orphan*/  callbacks; } ;

/* Variables and functions */
 int /*<<< orphan*/  QUEUE_FLAG_STATS ; 
 int /*<<< orphan*/  blk_queue_flag_clear (int /*<<< orphan*/ ,struct request_queue*) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del_rcu (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void blk_stat_remove_callback(struct request_queue *q,
			      struct blk_stat_callback *cb)
{
	spin_lock(&q->stats->lock);
	list_del_rcu(&cb->list);
	if (list_empty(&q->stats->callbacks) && !q->stats->enable_accounting)
		blk_queue_flag_clear(QUEUE_FLAG_STATS, q);
	spin_unlock(&q->stats->lock);

	del_timer_sync(&cb->timer);
}