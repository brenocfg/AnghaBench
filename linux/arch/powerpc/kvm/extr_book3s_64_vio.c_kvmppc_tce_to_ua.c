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
struct kvm_memory_slot {int dummy; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 long EINVAL ; 
 unsigned long PAGE_MASK ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long TCE_PCI_READ ; 
 unsigned long TCE_PCI_WRITE ; 
 unsigned long __gfn_to_hva_memslot (struct kvm_memory_slot*,unsigned long) ; 
 int /*<<< orphan*/  kvm_memslots (struct kvm*) ; 
 struct kvm_memory_slot* search_memslots (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static long kvmppc_tce_to_ua(struct kvm *kvm, unsigned long tce,
		unsigned long *ua)
{
	unsigned long gfn = tce >> PAGE_SHIFT;
	struct kvm_memory_slot *memslot;

	memslot = search_memslots(kvm_memslots(kvm), gfn);
	if (!memslot)
		return -EINVAL;

	*ua = __gfn_to_hva_memslot(memslot, gfn) |
		(tce & ~(PAGE_MASK | TCE_PCI_READ | TCE_PCI_WRITE));

	return 0;
}