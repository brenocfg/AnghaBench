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
typedef  long u64 ;
struct pt_regs {long ip; long ax; long sp; } ;

/* Variables and functions */
 long HV_CRASH_CTL_CRASH_NOTIFY ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_CTL ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P0 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P1 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P2 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P3 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P4 ; 
 int /*<<< orphan*/  HV_X64_MSR_GUEST_OS_ID ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,long) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,long) ; 

void hyperv_report_panic(struct pt_regs *regs, long err)
{
	static bool panic_reported;
	u64 guest_id;

	/*
	 * We prefer to report panic on 'die' chain as we have proper
	 * registers to report, but if we miss it (e.g. on BUG()) we need
	 * to report it on 'panic'.
	 */
	if (panic_reported)
		return;
	panic_reported = true;

	rdmsrl(HV_X64_MSR_GUEST_OS_ID, guest_id);

	wrmsrl(HV_X64_MSR_CRASH_P0, err);
	wrmsrl(HV_X64_MSR_CRASH_P1, guest_id);
	wrmsrl(HV_X64_MSR_CRASH_P2, regs->ip);
	wrmsrl(HV_X64_MSR_CRASH_P3, regs->ax);
	wrmsrl(HV_X64_MSR_CRASH_P4, regs->sp);

	/*
	 * Let Hyper-V know there is crash data available
	 */
	wrmsrl(HV_X64_MSR_CRASH_CTL, HV_CRASH_CTL_CRASH_NOTIFY);
}