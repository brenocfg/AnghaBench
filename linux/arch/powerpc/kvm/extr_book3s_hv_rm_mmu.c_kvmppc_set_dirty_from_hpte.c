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
struct kvm_memory_slot {scalar_t__ dirty_bitmap; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 struct kvm_memory_slot* __gfn_to_memslot (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long hpte_rpn (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvm_memslots_raw (struct kvm*) ; 
 unsigned long kvmppc_actual_pgsz (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  kvmppc_update_dirty_map (struct kvm_memory_slot*,unsigned long,unsigned long) ; 

__attribute__((used)) static void kvmppc_set_dirty_from_hpte(struct kvm *kvm,
				unsigned long hpte_v, unsigned long hpte_gr)
{
	struct kvm_memory_slot *memslot;
	unsigned long gfn;
	unsigned long psize;

	psize = kvmppc_actual_pgsz(hpte_v, hpte_gr);
	gfn = hpte_rpn(hpte_gr, psize);
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	if (memslot && memslot->dirty_bitmap)
		kvmppc_update_dirty_map(memslot, gfn, psize);
}