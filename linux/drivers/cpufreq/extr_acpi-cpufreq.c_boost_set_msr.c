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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {int x86_vendor; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE ; 
 int /*<<< orphan*/  MSR_IA32_MISC_ENABLE_TURBO_DISABLE ; 
 int /*<<< orphan*/  MSR_K7_HWCR ; 
 int /*<<< orphan*/  MSR_K7_HWCR_CPB_DIS ; 
#define  X86_VENDOR_AMD 130 
#define  X86_VENDOR_HYGON 129 
#define  X86_VENDOR_INTEL 128 
 TYPE_1__ boot_cpu_data ; 
 int /*<<< orphan*/  rdmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wrmsrl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int boost_set_msr(bool enable)
{
	u32 msr_addr;
	u64 msr_mask, val;

	switch (boot_cpu_data.x86_vendor) {
	case X86_VENDOR_INTEL:
		msr_addr = MSR_IA32_MISC_ENABLE;
		msr_mask = MSR_IA32_MISC_ENABLE_TURBO_DISABLE;
		break;
	case X86_VENDOR_HYGON:
	case X86_VENDOR_AMD:
		msr_addr = MSR_K7_HWCR;
		msr_mask = MSR_K7_HWCR_CPB_DIS;
		break;
	default:
		return -EINVAL;
	}

	rdmsrl(msr_addr, val);

	if (enable)
		val &= ~msr_mask;
	else
		val |= msr_mask;

	wrmsrl(msr_addr, val);
	return 0;
}