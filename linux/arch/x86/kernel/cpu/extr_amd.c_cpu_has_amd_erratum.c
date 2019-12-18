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
typedef  int u32 ;
struct cpuinfo_x86 {int x86_model; int x86_stepping; scalar_t__ x86; } ;

/* Variables and functions */
 int AMD_MODEL_RANGE_END (int) ; 
 scalar_t__ AMD_MODEL_RANGE_FAMILY (int) ; 
 int AMD_MODEL_RANGE_START (int) ; 
 scalar_t__ MSR_AMD64_OSVW_ID_LENGTH ; 
 scalar_t__ MSR_AMD64_OSVW_STATUS ; 
 int /*<<< orphan*/  X86_FEATURE_OSVW ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsrl (scalar_t__,int) ; 

__attribute__((used)) static bool cpu_has_amd_erratum(struct cpuinfo_x86 *cpu, const int *erratum)
{
	int osvw_id = *erratum++;
	u32 range;
	u32 ms;

	if (osvw_id >= 0 && osvw_id < 65536 &&
	    cpu_has(cpu, X86_FEATURE_OSVW)) {
		u64 osvw_len;

		rdmsrl(MSR_AMD64_OSVW_ID_LENGTH, osvw_len);
		if (osvw_id < osvw_len) {
			u64 osvw_bits;

			rdmsrl(MSR_AMD64_OSVW_STATUS + (osvw_id >> 6),
			    osvw_bits);
			return osvw_bits & (1ULL << (osvw_id & 0x3f));
		}
	}

	/* OSVW unavailable or ID unknown, match family-model-stepping range */
	ms = (cpu->x86_model << 4) | cpu->x86_stepping;
	while ((range = *erratum++))
		if ((cpu->x86 == AMD_MODEL_RANGE_FAMILY(range)) &&
		    (ms >= AMD_MODEL_RANGE_START(range)) &&
		    (ms <= AMD_MODEL_RANGE_END(range)))
			return true;

	return false;
}