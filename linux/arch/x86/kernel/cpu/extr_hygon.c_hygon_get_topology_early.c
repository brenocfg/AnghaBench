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
struct cpuinfo_x86 {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_TOPOEXT ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int cpuid_ebx (int) ; 
 int smp_num_siblings ; 

__attribute__((used)) static void hygon_get_topology_early(struct cpuinfo_x86 *c)
{
	if (cpu_has(c, X86_FEATURE_TOPOEXT))
		smp_num_siblings = ((cpuid_ebx(0x8000001e) >> 8) & 0xff) + 1;
}