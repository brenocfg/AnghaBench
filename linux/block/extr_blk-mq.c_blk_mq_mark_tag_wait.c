#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  entry; int /*<<< orphan*/  flags; } ;
typedef  TYPE_2__ wait_queue_entry_t ;
struct wait_queue_head {int /*<<< orphan*/  lock; } ;
struct sbitmap_queue {int /*<<< orphan*/  ws_active; } ;
struct request {int dummy; } ;
struct blk_mq_hw_ctx {int flags; int /*<<< orphan*/  dispatch_wait_lock; TYPE_2__ dispatch_wait; TYPE_1__* tags; } ;
struct TYPE_7__ {struct wait_queue_head wait; } ;
struct TYPE_5__ {struct sbitmap_queue bitmap_tags; } ;

/* Variables and functions */
 int BLK_MQ_F_TAG_SHARED ; 
 int /*<<< orphan*/  WQ_FLAG_EXCLUSIVE ; 
 int /*<<< orphan*/  __add_wait_queue (struct wait_queue_head*,TYPE_2__*) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int blk_mq_get_driver_tag (struct request*) ; 
 int /*<<< orphan*/  blk_mq_sched_mark_restart_hctx (struct blk_mq_hw_ctx*) ; 
 TYPE_3__* bt_wait_ptr (struct sbitmap_queue*,struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty_careful (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool blk_mq_mark_tag_wait(struct blk_mq_hw_ctx *hctx,
				 struct request *rq)
{
	struct sbitmap_queue *sbq = &hctx->tags->bitmap_tags;
	struct wait_queue_head *wq;
	wait_queue_entry_t *wait;
	bool ret;

	if (!(hctx->flags & BLK_MQ_F_TAG_SHARED)) {
		blk_mq_sched_mark_restart_hctx(hctx);

		/*
		 * It's possible that a tag was freed in the window between the
		 * allocation failure and adding the hardware queue to the wait
		 * queue.
		 *
		 * Don't clear RESTART here, someone else could have set it.
		 * At most this will cost an extra queue run.
		 */
		return blk_mq_get_driver_tag(rq);
	}

	wait = &hctx->dispatch_wait;
	if (!list_empty_careful(&wait->entry))
		return false;

	wq = &bt_wait_ptr(sbq, hctx)->wait;

	spin_lock_irq(&wq->lock);
	spin_lock(&hctx->dispatch_wait_lock);
	if (!list_empty(&wait->entry)) {
		spin_unlock(&hctx->dispatch_wait_lock);
		spin_unlock_irq(&wq->lock);
		return false;
	}

	atomic_inc(&sbq->ws_active);
	wait->flags &= ~WQ_FLAG_EXCLUSIVE;
	__add_wait_queue(wq, wait);

	/*
	 * It's possible that a tag was freed in the window between the
	 * allocation failure and adding the hardware queue to the wait
	 * queue.
	 */
	ret = blk_mq_get_driver_tag(rq);
	if (!ret) {
		spin_unlock(&hctx->dispatch_wait_lock);
		spin_unlock_irq(&wq->lock);
		return false;
	}

	/*
	 * We got a tag, remove ourselves from the wait queue to ensure
	 * someone else gets the wakeup.
	 */
	list_del_init(&wait->entry);
	atomic_dec(&sbq->ws_active);
	spin_unlock(&hctx->dispatch_wait_lock);
	spin_unlock_irq(&wq->lock);

	return true;
}