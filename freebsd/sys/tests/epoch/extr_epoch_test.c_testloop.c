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
 int ET_EXITING ; 
 int /*<<< orphan*/  epoch_testcase1 (void*) ; 
 int /*<<< orphan*/  epoch_testcase2 (void*) ; 
 int /*<<< orphan*/  kthread_exit () ; 
 int /*<<< orphan*/  msleep (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pause (char*,int) ; 
 int state_flags ; 
 int /*<<< orphan*/  state_mtx ; 

__attribute__((used)) static void
testloop(void *arg) {

	mtx_lock(&state_mtx);
	while ((state_flags & ET_EXITING) == 0) {
		msleep(&state_mtx, &state_mtx, 0, "epoch start wait", 0);
		if (state_flags & ET_EXITING)
			goto out;
		mtx_unlock(&state_mtx);
		epoch_testcase2(arg);
		pause("W", 500);
		epoch_testcase1(arg);
		mtx_lock(&state_mtx);
	}
 out:
	mtx_unlock(&state_mtx);
	kthread_exit();
}