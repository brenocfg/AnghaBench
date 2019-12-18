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
typedef  int /*<<< orphan*/  u64 ;
struct page {int dummy; } ;
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {unsigned int access; int /*<<< orphan*/  level; } ;
struct kvm_mmu_page {int spt; TYPE_1__ role; } ;
struct kvm_memory_slot {int dummy; } ;
typedef  int /*<<< orphan*/  gfn_t ;

/* Variables and functions */
 unsigned int ACC_WRITE_MASK ; 
 int PTE_PREFETCH_NUM ; 
 struct kvm_memory_slot* gfn_to_memslot_dirty_bitmap (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned int) ; 
 int gfn_to_page_many_atomic (struct kvm_memory_slot*,int /*<<< orphan*/ ,struct page**,int) ; 
 int /*<<< orphan*/  kvm_mmu_page_get_gfn (struct kvm_mmu_page*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mmu_set_spte (struct kvm_vcpu*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  page_to_pfn (struct page*) ; 
 int /*<<< orphan*/  put_page (struct page*) ; 

__attribute__((used)) static int direct_pte_prefetch_many(struct kvm_vcpu *vcpu,
				    struct kvm_mmu_page *sp,
				    u64 *start, u64 *end)
{
	struct page *pages[PTE_PREFETCH_NUM];
	struct kvm_memory_slot *slot;
	unsigned access = sp->role.access;
	int i, ret;
	gfn_t gfn;

	gfn = kvm_mmu_page_get_gfn(sp, start - sp->spt);
	slot = gfn_to_memslot_dirty_bitmap(vcpu, gfn, access & ACC_WRITE_MASK);
	if (!slot)
		return -1;

	ret = gfn_to_page_many_atomic(slot, gfn, pages, end - start);
	if (ret <= 0)
		return -1;

	for (i = 0; i < ret; i++, gfn++, start++) {
		mmu_set_spte(vcpu, start, access, 0, sp->role.level, gfn,
			     page_to_pfn(pages[i]), true, true);
		put_page(pages[i]);
	}

	return 0;
}