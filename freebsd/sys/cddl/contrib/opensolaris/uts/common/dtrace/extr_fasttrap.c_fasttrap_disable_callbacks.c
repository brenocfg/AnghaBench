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
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/ * dtrace_pid_probe_ptr ; 
 int /*<<< orphan*/ * dtrace_return_probe_ptr ; 
 int /*<<< orphan*/  dtrace_sync () ; 
 int /*<<< orphan*/  fasttrap_count_mtx ; 
 scalar_t__ fasttrap_pid_count ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fasttrap_disable_callbacks(void)
{
	mutex_enter(&fasttrap_count_mtx);
	ASSERT(fasttrap_pid_count > 0);
	fasttrap_pid_count--;
	if (fasttrap_pid_count == 0) {
		/*
		 * Synchronize with the breakpoint handler, which is careful to
		 * enable interrupts only after loading the hook pointer.
		 */
		dtrace_sync();
		dtrace_pid_probe_ptr = NULL;
		dtrace_return_probe_ptr = NULL;
	}
	mutex_exit(&fasttrap_count_mtx);
}