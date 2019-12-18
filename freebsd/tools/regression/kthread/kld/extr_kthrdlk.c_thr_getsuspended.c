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

/* Variables and functions */
 int QUIT ; 
 int /*<<< orphan*/  global_condvar ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  kthread_suspend_check () ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_global_lock ; 
 int /*<<< orphan*/  test_thrcnt ; 
 int /*<<< orphan*/  wakeup (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
thr_getsuspended(void *arg)
{
	for (;;) {
		if (QUIT == 1)
			break;
		kthread_suspend_check();
	}

	mtx_lock(&test_global_lock);
	test_thrcnt--;
	wakeup(&global_condvar);
	mtx_unlock(&test_global_lock);

	kthread_exit();
}