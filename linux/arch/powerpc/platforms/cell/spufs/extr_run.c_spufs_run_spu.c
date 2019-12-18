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
typedef  int u32 ;
struct TYPE_2__ {int /*<<< orphan*/  libassist; } ;
struct spu_context {int event_return; int /*<<< orphan*/  run_mutex; TYPE_1__ stats; int /*<<< orphan*/  sched_flags; struct spu* spu; int /*<<< orphan*/  state_mutex; int /*<<< orphan*/  stop_wq; } ;
struct spu {int dummy; } ;

/* Variables and functions */
 long ERESTARTSYS ; 
 int /*<<< orphan*/  SIGTRAP ; 
 int /*<<< orphan*/  SPU_SCHED_NOTIFY_ACTIVE ; 
 int SPU_STATUS_SINGLE_STEP ; 
 int SPU_STATUS_STOPPED_BY_HALT ; 
 int SPU_STATUS_STOPPED_BY_STOP ; 
 int SPU_STOP_STATUS_SHIFT ; 
 int /*<<< orphan*/  SPU_UTIL_SYSTEM ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  force_sig (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 scalar_t__ mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int spu_acquire (struct spu_context*) ; 
 int /*<<< orphan*/  spu_disable_spu (struct spu_context*) ; 
 int /*<<< orphan*/  spu_enable_spu (struct spu_context*) ; 
 int spu_process_callback (struct spu_context*) ; 
 int /*<<< orphan*/  spu_release (struct spu_context*) ; 
 int spu_run_fini (struct spu_context*,int*,int*) ; 
 int spu_run_init (struct spu_context*,int*) ; 
 int /*<<< orphan*/  spu_stopped (struct spu_context*,int*) ; 
 int /*<<< orphan*/  spu_switch_notify (struct spu*,struct spu_context*) ; 
 int /*<<< orphan*/  spu_update_sched_info (struct spu_context*) ; 
 int /*<<< orphan*/  spu_yield (struct spu_context*) ; 
 int /*<<< orphan*/  spuctx_switch_state (struct spu_context*,int /*<<< orphan*/ ) ; 
 int spufs_handle_class0 (struct spu_context*) ; 
 int spufs_handle_class1 (struct spu_context*) ; 
 int spufs_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

long spufs_run_spu(struct spu_context *ctx, u32 *npc, u32 *event)
{
	int ret;
	struct spu *spu;
	u32 status;

	if (mutex_lock_interruptible(&ctx->run_mutex))
		return -ERESTARTSYS;

	ctx->event_return = 0;

	ret = spu_acquire(ctx);
	if (ret)
		goto out_unlock;

	spu_enable_spu(ctx);

	spu_update_sched_info(ctx);

	ret = spu_run_init(ctx, npc);
	if (ret) {
		spu_release(ctx);
		goto out;
	}

	do {
		ret = spufs_wait(ctx->stop_wq, spu_stopped(ctx, &status));
		if (unlikely(ret)) {
			/*
			 * This is nasty: we need the state_mutex for all the
			 * bookkeeping even if the syscall was interrupted by
			 * a signal. ewww.
			 */
			mutex_lock(&ctx->state_mutex);
			break;
		}
		spu = ctx->spu;
		if (unlikely(test_and_clear_bit(SPU_SCHED_NOTIFY_ACTIVE,
						&ctx->sched_flags))) {
			if (!(status & SPU_STATUS_STOPPED_BY_STOP)) {
				spu_switch_notify(spu, ctx);
				continue;
			}
		}

		spuctx_switch_state(ctx, SPU_UTIL_SYSTEM);

		if ((status & SPU_STATUS_STOPPED_BY_STOP) &&
		    (status >> SPU_STOP_STATUS_SHIFT == 0x2104)) {
			ret = spu_process_callback(ctx);
			if (ret)
				break;
			status &= ~SPU_STATUS_STOPPED_BY_STOP;
		}
		ret = spufs_handle_class1(ctx);
		if (ret)
			break;

		ret = spufs_handle_class0(ctx);
		if (ret)
			break;

		if (signal_pending(current))
			ret = -ERESTARTSYS;
	} while (!ret && !(status & (SPU_STATUS_STOPPED_BY_STOP |
				      SPU_STATUS_STOPPED_BY_HALT |
				       SPU_STATUS_SINGLE_STEP)));

	spu_disable_spu(ctx);
	ret = spu_run_fini(ctx, npc, &status);
	spu_yield(ctx);

	if ((status & SPU_STATUS_STOPPED_BY_STOP) &&
	    (((status >> SPU_STOP_STATUS_SHIFT) & 0x3f00) == 0x2100))
		ctx->stats.libassist++;

	if ((ret == 0) ||
	    ((ret == -ERESTARTSYS) &&
	     ((status & SPU_STATUS_STOPPED_BY_HALT) ||
	      (status & SPU_STATUS_SINGLE_STEP) ||
	      ((status & SPU_STATUS_STOPPED_BY_STOP) &&
	       (status >> SPU_STOP_STATUS_SHIFT != 0x2104)))))
		ret = status;

	/* Note: we don't need to force_sig SIGTRAP on single-step
	 * since we have TIF_SINGLESTEP set, thus the kernel will do
	 * it upon return from the syscall anyway.
	 */
	if (unlikely(status & SPU_STATUS_SINGLE_STEP))
		ret = -ERESTARTSYS;

	else if (unlikely((status & SPU_STATUS_STOPPED_BY_STOP)
	    && (status >> SPU_STOP_STATUS_SHIFT) == 0x3fff)) {
		force_sig(SIGTRAP);
		ret = -ERESTARTSYS;
	}

out:
	*event = ctx->event_return;
out_unlock:
	mutex_unlock(&ctx->run_mutex);
	return ret;
}