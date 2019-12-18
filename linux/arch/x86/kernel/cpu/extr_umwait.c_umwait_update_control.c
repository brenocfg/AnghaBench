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
typedef  int u32 ;

/* Variables and functions */
 int MSR_IA32_UMWAIT_CONTROL_C02_DISABLE ; 
 int MSR_IA32_UMWAIT_CONTROL_TIME_MASK ; 
 int /*<<< orphan*/  WRITE_ONCE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  umwait_control_cached ; 
 int /*<<< orphan*/  umwait_update_control_msr ; 

__attribute__((used)) static inline void umwait_update_control(u32 maxtime, bool c02_enable)
{
	u32 ctrl = maxtime & MSR_IA32_UMWAIT_CONTROL_TIME_MASK;

	if (!c02_enable)
		ctrl |= MSR_IA32_UMWAIT_CONTROL_C02_DISABLE;

	WRITE_ONCE(umwait_control_cached, ctrl);
	/* Propagate to all CPUs */
	on_each_cpu(umwait_update_control_msr, NULL, 1);
}