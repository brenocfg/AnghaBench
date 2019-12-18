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
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct kvm_mmu {int /*<<< orphan*/ * pae_root; } ;
struct TYPE_2__ {scalar_t__ (* get_tdp_level ) (struct kvm_vcpu*) ;} ;

/* Variables and functions */
 int ENOMEM ; 
 int GFP_KERNEL_ACCOUNT ; 
 int /*<<< orphan*/  INVALID_PAGE ; 
 scalar_t__ PT32E_ROOT_LEVEL ; 
 int __GFP_DMA32 ; 
 struct page* alloc_page (int) ; 
 TYPE_1__* kvm_x86_ops ; 
 int /*<<< orphan*/ * page_address (struct page*) ; 
 scalar_t__ stub1 (struct kvm_vcpu*) ; 
 scalar_t__ tdp_enabled ; 

__attribute__((used)) static int alloc_mmu_pages(struct kvm_vcpu *vcpu, struct kvm_mmu *mmu)
{
	struct page *page;
	int i;

	/*
	 * When using PAE paging, the four PDPTEs are treated as 'root' pages,
	 * while the PDP table is a per-vCPU construct that's allocated at MMU
	 * creation.  When emulating 32-bit mode, cr3 is only 32 bits even on
	 * x86_64.  Therefore we need to allocate the PDP table in the first
	 * 4GB of memory, which happens to fit the DMA32 zone.  Except for
	 * SVM's 32-bit NPT support, TDP paging doesn't use PAE paging and can
	 * skip allocating the PDP table.
	 */
	if (tdp_enabled && kvm_x86_ops->get_tdp_level(vcpu) > PT32E_ROOT_LEVEL)
		return 0;

	page = alloc_page(GFP_KERNEL_ACCOUNT | __GFP_DMA32);
	if (!page)
		return -ENOMEM;

	mmu->pae_root = page_address(page);
	for (i = 0; i < 4; ++i)
		mmu->pae_root[i] = INVALID_PAGE;

	return 0;
}