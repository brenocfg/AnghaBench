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
struct cpuinfo_x86 {int x86; int x86_model; int x86_cache_bits; } ;

/* Variables and functions */
#define  INTEL_FAM6_BROADWELL 140 
#define  INTEL_FAM6_BROADWELL_G 139 
#define  INTEL_FAM6_HASWELL 138 
#define  INTEL_FAM6_HASWELL_G 137 
#define  INTEL_FAM6_HASWELL_L 136 
#define  INTEL_FAM6_IVYBRIDGE 135 
#define  INTEL_FAM6_KABYLAKE 134 
#define  INTEL_FAM6_KABYLAKE_L 133 
#define  INTEL_FAM6_NEHALEM 132 
#define  INTEL_FAM6_SANDYBRIDGE 131 
#define  INTEL_FAM6_SKYLAKE 130 
#define  INTEL_FAM6_SKYLAKE_L 129 
#define  INTEL_FAM6_WESTMERE 128 

__attribute__((used)) static void override_cache_bits(struct cpuinfo_x86 *c)
{
	if (c->x86 != 6)
		return;

	switch (c->x86_model) {
	case INTEL_FAM6_NEHALEM:
	case INTEL_FAM6_WESTMERE:
	case INTEL_FAM6_SANDYBRIDGE:
	case INTEL_FAM6_IVYBRIDGE:
	case INTEL_FAM6_HASWELL:
	case INTEL_FAM6_HASWELL_L:
	case INTEL_FAM6_HASWELL_G:
	case INTEL_FAM6_BROADWELL:
	case INTEL_FAM6_BROADWELL_G:
	case INTEL_FAM6_SKYLAKE_L:
	case INTEL_FAM6_SKYLAKE:
	case INTEL_FAM6_KABYLAKE_L:
	case INTEL_FAM6_KABYLAKE:
		if (c->x86_cache_bits < 44)
			c->x86_cache_bits = 44;
		break;
	}
}