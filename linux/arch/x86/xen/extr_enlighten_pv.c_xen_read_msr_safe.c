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

/* Variables and functions */
#define  MSR_IA32_APICBASE 128 
 int /*<<< orphan*/  X2APIC_ENABLE ; 
 int /*<<< orphan*/  native_read_msr_safe (unsigned int,int*) ; 
 scalar_t__ pmu_msr_read (unsigned int,int /*<<< orphan*/ *,int*) ; 

__attribute__((used)) static u64 xen_read_msr_safe(unsigned int msr, int *err)
{
	u64 val;

	if (pmu_msr_read(msr, &val, err))
		return val;

	val = native_read_msr_safe(msr, err);
	switch (msr) {
	case MSR_IA32_APICBASE:
		val &= ~X2APIC_ENABLE;
		break;
	}
	return val;
}