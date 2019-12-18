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
typedef  int u64 ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  HYPERVISOR_set_segment_base (unsigned int,int) ; 
#define  MSR_CSTAR 137 
#define  MSR_FS_BASE 136 
#define  MSR_GS_BASE 135 
#define  MSR_IA32_SYSENTER_CS 134 
#define  MSR_IA32_SYSENTER_EIP 133 
#define  MSR_IA32_SYSENTER_ESP 132 
#define  MSR_KERNEL_GS_BASE 131 
#define  MSR_LSTAR 130 
#define  MSR_STAR 129 
#define  MSR_SYSCALL_MASK 128 
 unsigned int SEGBASE_FS ; 
 unsigned int SEGBASE_GS_KERNEL ; 
 unsigned int SEGBASE_GS_USER ; 
 int native_write_msr_safe (unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  pmu_msr_write (unsigned int,unsigned int,unsigned int,int*) ; 

__attribute__((used)) static int xen_write_msr_safe(unsigned int msr, unsigned low, unsigned high)
{
	int ret;

	ret = 0;

	switch (msr) {
#ifdef CONFIG_X86_64
		unsigned which;
		u64 base;

	case MSR_FS_BASE:		which = SEGBASE_FS; goto set;
	case MSR_KERNEL_GS_BASE:	which = SEGBASE_GS_USER; goto set;
	case MSR_GS_BASE:		which = SEGBASE_GS_KERNEL; goto set;

	set:
		base = ((u64)high << 32) | low;
		if (HYPERVISOR_set_segment_base(which, base) != 0)
			ret = -EIO;
		break;
#endif

	case MSR_STAR:
	case MSR_CSTAR:
	case MSR_LSTAR:
	case MSR_SYSCALL_MASK:
	case MSR_IA32_SYSENTER_CS:
	case MSR_IA32_SYSENTER_ESP:
	case MSR_IA32_SYSENTER_EIP:
		/* Fast syscall setup is all done in hypercalls, so
		   these are all ignored.  Stub them out here to stop
		   Xen console noise. */
		break;

	default:
		if (!pmu_msr_write(msr, low, high, &ret))
			ret = native_write_msr_safe(msr, low, high);
	}

	return ret;
}