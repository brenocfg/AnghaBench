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
 int /*<<< orphan*/  MULTI_update_va_mapping (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  PAGE_KERNEL ; 
 scalar_t__ PAGE_SIZE ; 
 unsigned int UVMF_ALL ; 
 unsigned int UVMF_INVLPG ; 
 unsigned int UVMF_TLB_FLUSH ; 
 struct multicall_space __xen_mc_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mfn_pte (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_phys_to_machine (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  virt_to_pfn (unsigned long) ; 
 int /*<<< orphan*/  xen_mc_batch () ; 
 int /*<<< orphan*/  xen_mc_issue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void xen_remap_exchanged_ptes(unsigned long vaddr, int order,
				     unsigned long *mfns,
				     unsigned long first_mfn)
{
	unsigned i, limit;
	unsigned long mfn;

	xen_mc_batch();

	limit = 1u << order;
	for (i = 0; i < limit; i++, vaddr += PAGE_SIZE) {
		struct multicall_space mcs;
		unsigned flags;

		mcs = __xen_mc_entry(0);
		if (mfns)
			mfn = mfns[i];
		else
			mfn = first_mfn + i;

		if (i < (limit - 1))
			flags = 0;
		else {
			if (order == 0)
				flags = UVMF_INVLPG | UVMF_ALL;
			else
				flags = UVMF_TLB_FLUSH | UVMF_ALL;
		}

		MULTI_update_va_mapping(mcs.mc, vaddr,
				mfn_pte(mfn, PAGE_KERNEL), flags);

		set_phys_to_machine(virt_to_pfn(vaddr), mfn);
	}

	xen_mc_issue(0);
}