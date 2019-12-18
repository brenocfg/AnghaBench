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
struct spu_context {int flags; int /*<<< orphan*/  stop_wq; int /*<<< orphan*/  state_mutex; } ;
struct TYPE_2__ {int /*<<< orphan*/  runq_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DEFINE_WAIT (int /*<<< orphan*/ ) ; 
 int SPU_CREATE_NOSCHED ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __spu_add_to_rq (struct spu_context*) ; 
 int /*<<< orphan*/  __spu_del_from_rq (struct spu_context*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prepare_to_wait_exclusive (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* spu_prio ; 
 int /*<<< orphan*/  wait ; 

__attribute__((used)) static void spu_prio_wait(struct spu_context *ctx)
{
	DEFINE_WAIT(wait);

	/*
	 * The caller must explicitly wait for a context to be loaded
	 * if the nosched flag is set.  If NOSCHED is not set, the caller
	 * queues the context and waits for an spu event or error.
	 */
	BUG_ON(!(ctx->flags & SPU_CREATE_NOSCHED));

	spin_lock(&spu_prio->runq_lock);
	prepare_to_wait_exclusive(&ctx->stop_wq, &wait, TASK_INTERRUPTIBLE);
	if (!signal_pending(current)) {
		__spu_add_to_rq(ctx);
		spin_unlock(&spu_prio->runq_lock);
		mutex_unlock(&ctx->state_mutex);
		schedule();
		mutex_lock(&ctx->state_mutex);
		spin_lock(&spu_prio->runq_lock);
		__spu_del_from_rq(ctx);
	}
	spin_unlock(&spu_prio->runq_lock);
	__set_current_state(TASK_RUNNING);
	remove_wait_queue(&ctx->stop_wq, &wait);
}