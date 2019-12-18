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
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  TIF_NOCPUID ; 
 int /*<<< orphan*/  TIF_SSBD ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  enable_cpuid () ; 
 int /*<<< orphan*/  speculation_ctrl_update (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_clear_spec_ssb_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  task_clear_spec_ssb_noexec (int /*<<< orphan*/ ) ; 
 scalar_t__ task_spec_ssb_noexec (int /*<<< orphan*/ ) ; 
 TYPE_1__* task_thread_info (int /*<<< orphan*/ ) ; 
 scalar_t__ test_thread_flag (int /*<<< orphan*/ ) ; 

void arch_setup_new_exec(void)
{
	/* If cpuid was previously disabled for this task, re-enable it. */
	if (test_thread_flag(TIF_NOCPUID))
		enable_cpuid();

	/*
	 * Don't inherit TIF_SSBD across exec boundary when
	 * PR_SPEC_DISABLE_NOEXEC is used.
	 */
	if (test_thread_flag(TIF_SSBD) &&
	    task_spec_ssb_noexec(current)) {
		clear_thread_flag(TIF_SSBD);
		task_clear_spec_ssb_disable(current);
		task_clear_spec_ssb_noexec(current);
		speculation_ctrl_update(task_thread_info(current)->flags);
	}
}