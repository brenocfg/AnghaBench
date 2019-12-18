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
struct multicall_space {int /*<<< orphan*/  mc; } ;

/* Variables and functions */
 int /*<<< orphan*/  INVALID_P2M_ENTRY ; 
 int /*<<< orphan*/  MULTI_update_va_mapping (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  VOID_PTE ; 
 int /*<<< orphan*/  __set_phys_to_machine (unsigned long,int /*<<< orphan*/ ) ; 
 struct multicall_space __xen_mc_entry (int /*<<< orphan*/ ) ; 
 unsigned long virt_to_mfn (unsigned long) ; 
 unsigned long virt_to_pfn (unsigned long) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_zap_pfn_range(unsigned long vaddr, unsigned int order,
				unsigned long *in_frames,
				unsigned long *out_frames)
{
	int i;
	struct multicall_space mcs;

	xen_mc_batch();
	for (i = 0; i < (1UL<<order); i++, vaddr += PAGE_SIZE) {
		mcs = __xen_mc_entry(0);

		if (in_frames)
			in_frames[i] = virt_to_mfn(vaddr);

		MULTI_update_va_mapping(mcs.mc, vaddr, VOID_PTE, 0);
		__set_phys_to_machine(virt_to_pfn(vaddr), INVALID_P2M_ENTRY);

		if (out_frames)
			out_frames[i] = virt_to_pfn(vaddr);
	}
	xen_mc_issue(0);
}