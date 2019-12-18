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
 int /*<<< orphan*/  TIF_NOCPUID ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  set_cpuid_faulting (int) ; 
 int /*<<< orphan*/  test_and_set_thread_flag (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void disable_cpuid(void)
{
	preempt_disable();
	if (!test_and_set_thread_flag(TIF_NOCPUID)) {
		/*
		 * Must flip the CPU state synchronously with
		 * TIF_NOCPUID in the current running context.
		 */
		set_cpuid_faulting(true);
	}
	preempt_enable();
}