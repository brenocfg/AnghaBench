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
 int /*<<< orphan*/  ID_AA64MMFR0_ASID_SHIFT ; 
 int /*<<< orphan*/  ID_AA64MMFR0_EL1 ; 
 int cpuid_feature_extract_unsigned_field (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_warn (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_cpuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_processor_id () ; 

__attribute__((used)) static u32 get_cpu_asid_bits(void)
{
	u32 asid;
	int fld = cpuid_feature_extract_unsigned_field(read_cpuid(ID_AA64MMFR0_EL1),
						ID_AA64MMFR0_ASID_SHIFT);

	switch (fld) {
	default:
		pr_warn("CPU%d: Unknown ASID size (%d); assuming 8-bit\n",
					smp_processor_id(),  fld);
		/* Fallthrough */
	case 0:
		asid = 8;
		break;
	case 2:
		asid = 16;
	}

	return asid;
}