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
typedef  size_t phys_addr_t ;

/* Variables and functions */
 size_t HV_CRASH_CTL_CRASH_NOTIFY ; 
 size_t HV_CRASH_CTL_CRASH_NOTIFY_MSG ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_CTL ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P0 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P1 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P2 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P3 ; 
 int /*<<< orphan*/  HV_X64_MSR_CRASH_P4 ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,size_t) ; 

void hyperv_report_panic_msg(phys_addr_t pa, size_t size)
{
	/*
	 * P3 to contain the physical address of the panic page & P4 to
	 * contain the size of the panic data in that page. Rest of the
	 * registers are no-op when the NOTIFY_MSG flag is set.
	 */
	wrmsrl(HV_X64_MSR_CRASH_P0, 0);
	wrmsrl(HV_X64_MSR_CRASH_P1, 0);
	wrmsrl(HV_X64_MSR_CRASH_P2, 0);
	wrmsrl(HV_X64_MSR_CRASH_P3, pa);
	wrmsrl(HV_X64_MSR_CRASH_P4, size);

	/*
	 * Let Hyper-V know there is crash data available along with
	 * the panic message.
	 */
	wrmsrl(HV_X64_MSR_CRASH_CTL,
	       (HV_CRASH_CTL_CRASH_NOTIFY | HV_CRASH_CTL_CRASH_NOTIFY_MSG));
}