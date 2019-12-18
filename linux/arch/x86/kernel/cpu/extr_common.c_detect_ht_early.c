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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_CMP_LEGACY ; 
 int /*<<< orphan*/  X86_FEATURE_HT ; 
 int /*<<< orphan*/  X86_FEATURE_XTOPOLOGY ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 
 int /*<<< orphan*/  pr_info_once (char*) ; 
 int smp_num_siblings ; 

int detect_ht_early(struct cpuinfo_x86 *c)
{
#ifdef CONFIG_SMP
	u32 eax, ebx, ecx, edx;

	if (!cpu_has(c, X86_FEATURE_HT))
		return -1;

	if (cpu_has(c, X86_FEATURE_CMP_LEGACY))
		return -1;

	if (cpu_has(c, X86_FEATURE_XTOPOLOGY))
		return -1;

	cpuid(1, &eax, &ebx, &ecx, &edx);

	smp_num_siblings = (ebx & 0xff0000) >> 16;
	if (smp_num_siblings == 1)
		pr_info_once("CPU0: Hyper-Threading is disabled\n");
#endif
	return 0;
}