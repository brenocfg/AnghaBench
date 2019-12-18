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
struct TYPE_2__ {struct kvm_lpage_info** lpage_info; struct kvm_lpage_info** rmap; } ;
struct kvm_memory_slot {unsigned long base_gfn; unsigned long userspace_addr; TYPE_1__ arch; } ;
struct kvm_lpage_info {int disallow_lpage; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL_ACCOUNT ; 
 int KVM_NR_PAGE_SIZES ; 
 int KVM_PAGES_PER_HPAGE (int) ; 
 unsigned long PAGE_SHIFT ; 
 int gfn_to_index (unsigned long,unsigned long,int) ; 
 void* kvcalloc (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvfree (struct kvm_lpage_info*) ; 
 int /*<<< orphan*/  kvm_largepages_enabled () ; 
 scalar_t__ kvm_page_track_create_memslot (struct kvm_memory_slot*,unsigned long) ; 

int kvm_arch_create_memslot(struct kvm *kvm, struct kvm_memory_slot *slot,
			    unsigned long npages)
{
	int i;

	for (i = 0; i < KVM_NR_PAGE_SIZES; ++i) {
		struct kvm_lpage_info *linfo;
		unsigned long ugfn;
		int lpages;
		int level = i + 1;

		lpages = gfn_to_index(slot->base_gfn + npages - 1,
				      slot->base_gfn, level) + 1;

		slot->arch.rmap[i] =
			kvcalloc(lpages, sizeof(*slot->arch.rmap[i]),
				 GFP_KERNEL_ACCOUNT);
		if (!slot->arch.rmap[i])
			goto out_free;
		if (i == 0)
			continue;

		linfo = kvcalloc(lpages, sizeof(*linfo), GFP_KERNEL_ACCOUNT);
		if (!linfo)
			goto out_free;

		slot->arch.lpage_info[i - 1] = linfo;

		if (slot->base_gfn & (KVM_PAGES_PER_HPAGE(level) - 1))
			linfo[0].disallow_lpage = 1;
		if ((slot->base_gfn + npages) & (KVM_PAGES_PER_HPAGE(level) - 1))
			linfo[lpages - 1].disallow_lpage = 1;
		ugfn = slot->userspace_addr >> PAGE_SHIFT;
		/*
		 * If the gfn and userspace address are not aligned wrt each
		 * other, or if explicitly asked to, disable large page
		 * support for this slot
		 */
		if ((slot->base_gfn ^ ugfn) & (KVM_PAGES_PER_HPAGE(level) - 1) ||
		    !kvm_largepages_enabled()) {
			unsigned long j;

			for (j = 0; j < lpages; ++j)
				linfo[j].disallow_lpage = 1;
		}
	}

	if (kvm_page_track_create_memslot(slot, npages))
		goto out_free;

	return 0;

out_free:
	for (i = 0; i < KVM_NR_PAGE_SIZES; ++i) {
		kvfree(slot->arch.rmap[i]);
		slot->arch.rmap[i] = NULL;
		if (i == 0)
			continue;

		kvfree(slot->arch.lpage_info[i - 1]);
		slot->arch.lpage_info[i - 1] = NULL;
	}
	return -ENOMEM;
}