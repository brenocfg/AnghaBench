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
struct TYPE_2__ {scalar_t__ type; } ;
union _cpuid4_leaf_eax {unsigned int full; TYPE_1__ split; } ;
struct cpuinfo_x86 {scalar_t__ x86_vendor; } ;

/* Variables and functions */
 scalar_t__ CTYPE_NULL ; 
 scalar_t__ X86_VENDOR_AMD ; 
 scalar_t__ X86_VENDOR_HYGON ; 
 int /*<<< orphan*/  cpuid_count (unsigned int,int,unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static int find_num_cache_leaves(struct cpuinfo_x86 *c)
{
	unsigned int		eax, ebx, ecx, edx, op;
	union _cpuid4_leaf_eax	cache_eax;
	int 			i = -1;

	if (c->x86_vendor == X86_VENDOR_AMD ||
	    c->x86_vendor == X86_VENDOR_HYGON)
		op = 0x8000001d;
	else
		op = 4;

	do {
		++i;
		/* Do cpuid(op) loop to find out num_cache_leaves */
		cpuid_count(op, i, &eax, &ebx, &ecx, &edx);
		cache_eax.full = eax;
	} while (cache_eax.split.type != CTYPE_NULL);
	return i;
}