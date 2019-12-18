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

__attribute__((used)) static void p4_pmu_disable_pebs(void)
{
	/*
	 * FIXME
	 *
	 * It's still allowed that two threads setup same cache
	 * events so we can't simply clear metrics until we knew
	 * no one is depending on us, so we need kind of counter
	 * for "ReplayEvent" users.
	 *
	 * What is more complex -- RAW events, if user (for some
	 * reason) will pass some cache event metric with improper
	 * event opcode -- it's fine from hardware point of view
	 * but completely nonsense from "meaning" of such action.
	 *
	 * So at moment let leave metrics turned on forever -- it's
	 * ok for now but need to be revisited!
	 *
	 * (void)wrmsrl_safe(MSR_IA32_PEBS_ENABLE, 0);
	 * (void)wrmsrl_safe(MSR_P4_PEBS_MATRIX_VERT, 0);
	 */
}