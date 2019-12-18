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
struct TYPE_2__ {unsigned long* rmap; } ;
struct kvm_memory_slot {unsigned long base_gfn; TYPE_1__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 
 unsigned long PTE_RPN_MASK ; 
 int /*<<< orphan*/  kvmhv_remove_nest_rmap_list (struct kvm*,unsigned long*,unsigned long,unsigned long) ; 

void kvmhv_remove_nest_rmap_range(struct kvm *kvm,
				  const struct kvm_memory_slot *memslot,
				  unsigned long gpa, unsigned long hpa,
				  unsigned long nbytes)
{
	unsigned long gfn, end_gfn;
	unsigned long addr_mask;

	if (!memslot)
		return;
	gfn = (gpa >> PAGE_SHIFT) - memslot->base_gfn;
	end_gfn = gfn + (nbytes >> PAGE_SHIFT);

	addr_mask = PTE_RPN_MASK & ~(nbytes - 1);
	hpa &= addr_mask;

	for (; gfn < end_gfn; gfn++) {
		unsigned long *rmap = &memslot->arch.rmap[gfn];
		kvmhv_remove_nest_rmap_list(kvm, rmap, hpa, addr_mask);
	}
}