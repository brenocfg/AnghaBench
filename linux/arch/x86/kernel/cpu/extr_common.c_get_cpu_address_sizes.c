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
struct cpuinfo_x86 {int extended_cpuid_level; int x86_virt_bits; int x86_phys_bits; int x86_cache_bits; } ;

/* Variables and functions */
 int /*<<< orphan*/  X86_FEATURE_PAE ; 
 int /*<<< orphan*/  X86_FEATURE_PSE36 ; 
 scalar_t__ cpu_has (struct cpuinfo_x86*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 

void get_cpu_address_sizes(struct cpuinfo_x86 *c)
{
	u32 eax, ebx, ecx, edx;

	if (c->extended_cpuid_level >= 0x80000008) {
		cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

		c->x86_virt_bits = (eax >> 8) & 0xff;
		c->x86_phys_bits = eax & 0xff;
	}
#ifdef CONFIG_X86_32
	else if (cpu_has(c, X86_FEATURE_PAE) || cpu_has(c, X86_FEATURE_PSE36))
		c->x86_phys_bits = 36;
#endif
	c->x86_cache_bits = c->x86_phys_bits;
}