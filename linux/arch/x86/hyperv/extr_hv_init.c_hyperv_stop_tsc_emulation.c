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
typedef  int /*<<< orphan*/  u64 ;
struct hv_tsc_emulation_status {scalar_t__ inprogress; } ;

/* Variables and functions */
 int /*<<< orphan*/  HV_X64_MSR_TSC_EMULATION_STATUS ; 
 int /*<<< orphan*/  HV_X64_MSR_TSC_FREQUENCY ; 
 int /*<<< orphan*/  div64_u64 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tsc_khz ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void hyperv_stop_tsc_emulation(void)
{
	u64 freq;
	struct hv_tsc_emulation_status emu_status;

	rdmsrl(HV_X64_MSR_TSC_EMULATION_STATUS, *(u64 *)&emu_status);
	emu_status.inprogress = 0;
	wrmsrl(HV_X64_MSR_TSC_EMULATION_STATUS, *(u64 *)&emu_status);

	rdmsrl(HV_X64_MSR_TSC_FREQUENCY, freq);
	tsc_khz = div64_u64(freq, 1000);
}