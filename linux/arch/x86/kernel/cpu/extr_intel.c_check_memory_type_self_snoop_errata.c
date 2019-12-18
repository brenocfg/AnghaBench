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
struct cpuinfo_x86 {int x86_model; } ;

/* Variables and functions */
#define  INTEL_FAM6_CORE2_DUNNINGTON 139 
#define  INTEL_FAM6_CORE2_MEROM 138 
#define  INTEL_FAM6_CORE2_MEROM_L 137 
#define  INTEL_FAM6_CORE2_PENRYN 136 
#define  INTEL_FAM6_CORE_YONAH 135 
#define  INTEL_FAM6_NEHALEM 134 
#define  INTEL_FAM6_NEHALEM_EP 133 
#define  INTEL_FAM6_NEHALEM_EX 132 
#define  INTEL_FAM6_NEHALEM_G 131 
#define  INTEL_FAM6_SANDYBRIDGE 130 
#define  INTEL_FAM6_WESTMERE 129 
#define  INTEL_FAM6_WESTMERE_EP 128 
 int /*<<< orphan*/  X86_FEATURE_SELFSNOOP ; 
 int /*<<< orphan*/  setup_clear_cpu_cap (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void check_memory_type_self_snoop_errata(struct cpuinfo_x86 *c)
{
	switch (c->x86_model) {
	case INTEL_FAM6_CORE_YONAH:
	case INTEL_FAM6_CORE2_MEROM:
	case INTEL_FAM6_CORE2_MEROM_L:
	case INTEL_FAM6_CORE2_PENRYN:
	case INTEL_FAM6_CORE2_DUNNINGTON:
	case INTEL_FAM6_NEHALEM:
	case INTEL_FAM6_NEHALEM_G:
	case INTEL_FAM6_NEHALEM_EP:
	case INTEL_FAM6_NEHALEM_EX:
	case INTEL_FAM6_WESTMERE:
	case INTEL_FAM6_WESTMERE_EP:
	case INTEL_FAM6_SANDYBRIDGE:
		setup_clear_cpu_cap(X86_FEATURE_SELFSNOOP);
	}
}