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
struct wait_cb {int /*<<< orphan*/  cb; int /*<<< orphan*/  task; } ;
struct dma_fence {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_FENCE_FLAG_SIGNALED_BIT ; 
 long ERESTARTSYS ; 
 long ETIME ; 
 int TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int TASK_UNINTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 scalar_t__ dma_fence_add_callback (struct dma_fence*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_remove_callback (struct dma_fence*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mock_wakeup ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  set_current_state (int const) ; 
 scalar_t__ signal_pending_state (int const,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static long mock_wait(struct dma_fence *f, bool intr, long timeout)
{
	const int state = intr ? TASK_INTERRUPTIBLE : TASK_UNINTERRUPTIBLE;
	struct wait_cb cb = { .task = current };

	if (dma_fence_add_callback(f, &cb.cb, mock_wakeup))
		return timeout;

	while (timeout) {
		set_current_state(state);

		if (test_bit(DMA_FENCE_FLAG_SIGNALED_BIT, &f->flags))
			break;

		if (signal_pending_state(state, current))
			break;

		timeout = schedule_timeout(timeout);
	}
	__set_current_state(TASK_RUNNING);

	if (!dma_fence_remove_callback(f, &cb.cb))
		return timeout;

	if (signal_pending_state(state, current))
		return -ERESTARTSYS;

	return -ETIME;
}