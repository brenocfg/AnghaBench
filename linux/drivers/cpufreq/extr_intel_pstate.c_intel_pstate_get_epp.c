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
struct cpudata {int /*<<< orphan*/  cpu; } ;
typedef  int s16 ;

/* Variables and functions */
 int /*<<< orphan*/  MSR_HWP_REQUEST ; 
 int /*<<< orphan*/  X86_FEATURE_HWP_EPP ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 int intel_pstate_get_epb (struct cpudata*) ; 
 int rdmsrl_on_cpu (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static s16 intel_pstate_get_epp(struct cpudata *cpu_data, u64 hwp_req_data)
{
	s16 epp;

	if (boot_cpu_has(X86_FEATURE_HWP_EPP)) {
		/*
		 * When hwp_req_data is 0, means that caller didn't read
		 * MSR_HWP_REQUEST, so need to read and get EPP.
		 */
		if (!hwp_req_data) {
			epp = rdmsrl_on_cpu(cpu_data->cpu, MSR_HWP_REQUEST,
					    &hwp_req_data);
			if (epp)
				return epp;
		}
		epp = (hwp_req_data >> 24) & 0xff;
	} else {
		/* When there is no EPP present, HWP uses EPB settings */
		epp = intel_pstate_get_epb(cpu_data);
	}

	return epp;
}