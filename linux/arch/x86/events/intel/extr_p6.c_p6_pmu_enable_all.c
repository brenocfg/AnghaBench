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
 unsigned long ARCH_PERFMON_EVENTSEL_ENABLE ; 
 int /*<<< orphan*/  MSR_P6_EVNTSEL0 ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void p6_pmu_enable_all(int added)
{
	unsigned long val;

	/* p6 only has one enable register */
	rdmsrl(MSR_P6_EVNTSEL0, val);
	val |= ARCH_PERFMON_EVENTSEL_ENABLE;
	wrmsrl(MSR_P6_EVNTSEL0, val);
}