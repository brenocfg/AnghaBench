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
struct wait_timer {int /*<<< orphan*/  f; int /*<<< orphan*/  timer; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  ETIME ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  destroy_timer_on_stack (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dma_fence_put (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_fence_wait_timeout (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mock_fence () ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  pr_notice (char*) ; 
 scalar_t__ timer_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_setup_on_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_timer ; 

__attribute__((used)) static int test_wait_timeout(void *arg)
{
	struct wait_timer wt;
	int err = -EINVAL;

	timer_setup_on_stack(&wt.timer, wait_timer, 0);

	wt.f = mock_fence();
	if (!wt.f)
		return -ENOMEM;

	if (dma_fence_wait_timeout(wt.f, false, 1) != -ETIME) {
		pr_err("Wait reported complete before being signaled\n");
		goto err_free;
	}

	mod_timer(&wt.timer, jiffies + 1);

	if (dma_fence_wait_timeout(wt.f, false, 2) == -ETIME) {
		if (timer_pending(&wt.timer)) {
			pr_notice("Timer did not fire within the jiffie!\n");
			err = 0; /* not our fault! */
		} else {
			pr_err("Wait reported incomplete after timeout\n");
		}
		goto err_free;
	}

	err = 0;
err_free:
	del_timer_sync(&wt.timer);
	destroy_timer_on_stack(&wt.timer);
	dma_fence_signal(wt.f);
	dma_fence_put(wt.f);
	return err;
}