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
struct kvm_memory_slot {unsigned long base_gfn; unsigned long npages; TYPE_1__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 unsigned long KVMPPC_RMAP_PRESENT ; 
 scalar_t__ kvm_is_radix (struct kvm*) ; 
 int /*<<< orphan*/  kvm_unmap_rmapp (struct kvm*,struct kvm_memory_slot*,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_radix_flush_memslot (struct kvm*,struct kvm_memory_slot*) ; 

void kvmppc_core_flush_memslot_hv(struct kvm *kvm,
				  struct kvm_memory_slot *memslot)
{
	unsigned long gfn;
	unsigned long n;
	unsigned long *rmapp;

	gfn = memslot->base_gfn;
	rmapp = memslot->arch.rmap;
	if (kvm_is_radix(kvm)) {
		kvmppc_radix_flush_memslot(kvm, memslot);
		return;
	}

	for (n = memslot->npages; n; --n, ++gfn) {
		/*
		 * Testing the present bit without locking is OK because
		 * the memslot has been marked invalid already, and hence
		 * no new HPTEs referencing this page can be created,
		 * thus the present bit can't go from 0 to 1.
		 */
		if (*rmapp & KVMPPC_RMAP_PRESENT)
			kvm_unmap_rmapp(kvm, memslot, gfn);
		++rmapp;
	}
}