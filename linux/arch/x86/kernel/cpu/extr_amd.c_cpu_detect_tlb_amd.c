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
typedef  int u16 ;
struct cpuinfo_x86 {int x86; int extended_cpuid_level; int x86_model; } ;

/* Variables and functions */
 size_t ENTRIES ; 
 int /*<<< orphan*/  cpuid (int,int*,int*,int*,int*) ; 
 int cpuid_eax (int) ; 
 int* tlb_lld_2m ; 
 int* tlb_lld_4k ; 
 int* tlb_lld_4m ; 
 int* tlb_lli_2m ; 
 int* tlb_lli_4k ; 
 int* tlb_lli_4m ; 

__attribute__((used)) static void cpu_detect_tlb_amd(struct cpuinfo_x86 *c)
{
	u32 ebx, eax, ecx, edx;
	u16 mask = 0xfff;

	if (c->x86 < 0xf)
		return;

	if (c->extended_cpuid_level < 0x80000006)
		return;

	cpuid(0x80000006, &eax, &ebx, &ecx, &edx);

	tlb_lld_4k[ENTRIES] = (ebx >> 16) & mask;
	tlb_lli_4k[ENTRIES] = ebx & mask;

	/*
	 * K8 doesn't have 2M/4M entries in the L2 TLB so read out the L1 TLB
	 * characteristics from the CPUID function 0x80000005 instead.
	 */
	if (c->x86 == 0xf) {
		cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
		mask = 0xff;
	}

	/* Handle DTLB 2M and 4M sizes, fall back to L1 if L2 is disabled */
	if (!((eax >> 16) & mask))
		tlb_lld_2m[ENTRIES] = (cpuid_eax(0x80000005) >> 16) & 0xff;
	else
		tlb_lld_2m[ENTRIES] = (eax >> 16) & mask;

	/* a 4M entry uses two 2M entries */
	tlb_lld_4m[ENTRIES] = tlb_lld_2m[ENTRIES] >> 1;

	/* Handle ITLB 2M and 4M sizes, fall back to L1 if L2 is disabled */
	if (!(eax & mask)) {
		/* Erratum 658 */
		if (c->x86 == 0x15 && c->x86_model <= 0x1f) {
			tlb_lli_2m[ENTRIES] = 1024;
		} else {
			cpuid(0x80000005, &eax, &ebx, &ecx, &edx);
			tlb_lli_2m[ENTRIES] = eax & 0xff;
		}
	} else
		tlb_lli_2m[ENTRIES] = eax & mask;

	tlb_lli_4m[ENTRIES] = tlb_lli_2m[ENTRIES] >> 1;
}