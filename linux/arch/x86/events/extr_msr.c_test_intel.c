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
struct TYPE_2__ {scalar_t__ x86_vendor; int x86; int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_ATOM_AIRMONT 167 
#define  INTEL_FAM6_ATOM_GOLDMONT 166 
#define  INTEL_FAM6_ATOM_GOLDMONT_D 165 
#define  INTEL_FAM6_ATOM_GOLDMONT_PLUS 164 
#define  INTEL_FAM6_ATOM_SILVERMONT 163 
#define  INTEL_FAM6_ATOM_SILVERMONT_D 162 
#define  INTEL_FAM6_BROADWELL 161 
#define  INTEL_FAM6_BROADWELL_D 160 
#define  INTEL_FAM6_BROADWELL_G 159 
#define  INTEL_FAM6_BROADWELL_X 158 
#define  INTEL_FAM6_COMETLAKE 157 
#define  INTEL_FAM6_COMETLAKE_L 156 
#define  INTEL_FAM6_HASWELL 155 
#define  INTEL_FAM6_HASWELL_G 154 
#define  INTEL_FAM6_HASWELL_L 153 
#define  INTEL_FAM6_HASWELL_X 152 
#define  INTEL_FAM6_ICELAKE 151 
#define  INTEL_FAM6_ICELAKE_D 150 
#define  INTEL_FAM6_ICELAKE_L 149 
#define  INTEL_FAM6_ICELAKE_X 148 
#define  INTEL_FAM6_IVYBRIDGE 147 
#define  INTEL_FAM6_IVYBRIDGE_X 146 
#define  INTEL_FAM6_KABYLAKE 145 
#define  INTEL_FAM6_KABYLAKE_L 144 
#define  INTEL_FAM6_NEHALEM 143 
#define  INTEL_FAM6_NEHALEM_EP 142 
#define  INTEL_FAM6_NEHALEM_EX 141 
#define  INTEL_FAM6_NEHALEM_G 140 
#define  INTEL_FAM6_SANDYBRIDGE 139 
#define  INTEL_FAM6_SANDYBRIDGE_X 138 
#define  INTEL_FAM6_SKYLAKE 137 
#define  INTEL_FAM6_SKYLAKE_L 136 
#define  INTEL_FAM6_SKYLAKE_X 135 
#define  INTEL_FAM6_TIGERLAKE 134 
#define  INTEL_FAM6_TIGERLAKE_L 133 
#define  INTEL_FAM6_WESTMERE 132 
#define  INTEL_FAM6_WESTMERE_EP 131 
#define  INTEL_FAM6_WESTMERE_EX 130 
#define  INTEL_FAM6_XEON_PHI_KNL 129 
#define  INTEL_FAM6_XEON_PHI_KNM 128 
 int PERF_MSR_PPERF ; 
 int PERF_MSR_SMI ; 
 scalar_t__ X86_VENDOR_INTEL ; 
 TYPE_1__ boot_cpu_data ; 

__attribute__((used)) static bool test_intel(int idx, void *data)
{
	if (boot_cpu_data.x86_vendor != X86_VENDOR_INTEL ||
	    boot_cpu_data.x86 != 6)
		return false;

	switch (boot_cpu_data.x86_model) {
	case INTEL_FAM6_NEHALEM:
	case INTEL_FAM6_NEHALEM_G:
	case INTEL_FAM6_NEHALEM_EP:
	case INTEL_FAM6_NEHALEM_EX:

	case INTEL_FAM6_WESTMERE:
	case INTEL_FAM6_WESTMERE_EP:
	case INTEL_FAM6_WESTMERE_EX:

	case INTEL_FAM6_SANDYBRIDGE:
	case INTEL_FAM6_SANDYBRIDGE_X:

	case INTEL_FAM6_IVYBRIDGE:
	case INTEL_FAM6_IVYBRIDGE_X:

	case INTEL_FAM6_HASWELL:
	case INTEL_FAM6_HASWELL_X:
	case INTEL_FAM6_HASWELL_L:
	case INTEL_FAM6_HASWELL_G:

	case INTEL_FAM6_BROADWELL:
	case INTEL_FAM6_BROADWELL_D:
	case INTEL_FAM6_BROADWELL_G:
	case INTEL_FAM6_BROADWELL_X:

	case INTEL_FAM6_ATOM_SILVERMONT:
	case INTEL_FAM6_ATOM_SILVERMONT_D:
	case INTEL_FAM6_ATOM_AIRMONT:

	case INTEL_FAM6_ATOM_GOLDMONT:
	case INTEL_FAM6_ATOM_GOLDMONT_D:

	case INTEL_FAM6_ATOM_GOLDMONT_PLUS:

	case INTEL_FAM6_XEON_PHI_KNL:
	case INTEL_FAM6_XEON_PHI_KNM:
		if (idx == PERF_MSR_SMI)
			return true;
		break;

	case INTEL_FAM6_SKYLAKE_L:
	case INTEL_FAM6_SKYLAKE:
	case INTEL_FAM6_SKYLAKE_X:
	case INTEL_FAM6_KABYLAKE_L:
	case INTEL_FAM6_KABYLAKE:
	case INTEL_FAM6_COMETLAKE_L:
	case INTEL_FAM6_COMETLAKE:
	case INTEL_FAM6_ICELAKE_L:
	case INTEL_FAM6_ICELAKE:
	case INTEL_FAM6_ICELAKE_X:
	case INTEL_FAM6_ICELAKE_D:
	case INTEL_FAM6_TIGERLAKE_L:
	case INTEL_FAM6_TIGERLAKE:
		if (idx == PERF_MSR_SMI || idx == PERF_MSR_PPERF)
			return true;
		break;
	}

	return false;
}