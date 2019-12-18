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
typedef  void* u32 ;
struct cpuinfo_x86 {int x86_cache_max_rmid; int x86_cache_occ_scale; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_CQM_LLC ; 
 int /*<<< orphan*/  X86_FEATURE_CQM_MBM_LOCAL ; 
 int /*<<< orphan*/  X86_FEATURE_CQM_MBM_TOTAL ; 
 int /*<<< orphan*/  X86_FEATURE_CQM_OCCUP_LLC ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid_count (int,int,void**,void**,void**,void**) ; 
 int cpuid_ebx (int) ; 

__attribute__((used)) static void init_cqm(struct cpuinfo_x86 *c)
{
	if (!cpu_has(c, X86_FEATURE_CQM_LLC)) {
		c->x86_cache_max_rmid  = -1;
		c->x86_cache_occ_scale = -1;
		return;
	}

	/* will be overridden if occupancy monitoring exists */
	c->x86_cache_max_rmid = cpuid_ebx(0xf);

	if (cpu_has(c, X86_FEATURE_CQM_OCCUP_LLC) ||
	    cpu_has(c, X86_FEATURE_CQM_MBM_TOTAL) ||
	    cpu_has(c, X86_FEATURE_CQM_MBM_LOCAL)) {
		u32 eax, ebx, ecx, edx;

		/* QoS sub-leaf, EAX=0Fh, ECX=1 */
		cpuid_count(0xf, 1, &eax, &ebx, &ecx, &edx);

		c->x86_cache_max_rmid  = ecx;
		c->x86_cache_occ_scale = ebx;
	}
}