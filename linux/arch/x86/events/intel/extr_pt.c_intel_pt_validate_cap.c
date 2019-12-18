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
typedef  unsigned int u32 ;
struct pt_cap_desc {size_t leaf; size_t reg; unsigned int mask; } ;
typedef  enum pt_capabilities { ____Placeholder_pt_capabilities } pt_capabilities ;

/* Variables and functions */
 size_t PT_CPUID_REGS_NUM ; 
 unsigned int __ffs (unsigned int) ; 
 struct pt_cap_desc* pt_caps ; 

u32 intel_pt_validate_cap(u32 *caps, enum pt_capabilities capability)
{
	struct pt_cap_desc *cd = &pt_caps[capability];
	u32 c = caps[cd->leaf * PT_CPUID_REGS_NUM + cd->reg];
	unsigned int shift = __ffs(cd->mask);

	return (c & cd->mask) >> shift;
}