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
 int DEBUGCTLMSR_FREEZE_PERFMON_ON_PMI ; 
 int get_debugctlmsr () ; 
 int /*<<< orphan*/  update_debugctlmsr (int) ; 

__attribute__((used)) static void enable_counter_freeze(void)
{
	update_debugctlmsr(get_debugctlmsr() |
			DEBUGCTLMSR_FREEZE_PERFMON_ON_PMI);
}