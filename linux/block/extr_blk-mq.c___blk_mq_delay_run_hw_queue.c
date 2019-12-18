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
struct blk_mq_hw_ctx {int flags; int /*<<< orphan*/  run_work; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 int BLK_MQ_F_BLOCKING ; 
 int /*<<< orphan*/  __blk_mq_run_hw_queue (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_hctx_next_cpu (struct blk_mq_hw_ctx*) ; 
 int /*<<< orphan*/  blk_mq_hctx_stopped (struct blk_mq_hw_ctx*) ; 
 scalar_t__ cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int get_cpu () ; 
 int /*<<< orphan*/  kblockd_mod_delayed_work_on (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (unsigned long) ; 
 int /*<<< orphan*/  put_cpu () ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __blk_mq_delay_run_hw_queue(struct blk_mq_hw_ctx *hctx, bool async,
					unsigned long msecs)
{
	if (unlikely(blk_mq_hctx_stopped(hctx)))
		return;

	if (!async && !(hctx->flags & BLK_MQ_F_BLOCKING)) {
		int cpu = get_cpu();
		if (cpumask_test_cpu(cpu, hctx->cpumask)) {
			__blk_mq_run_hw_queue(hctx);
			put_cpu();
			return;
		}

		put_cpu();
	}

	kblockd_mod_delayed_work_on(blk_mq_hctx_next_cpu(hctx), &hctx->run_work,
				    msecs_to_jiffies(msecs));
}