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
struct TYPE_2__ {int /*<<< orphan*/ * rmap; } ;
struct kvm_memory_slot {unsigned long base_gfn; TYPE_1__ arch; } ;
struct kvm {int dummy; } ;

/* Variables and functions */
 struct kvm_memory_slot* __gfn_to_memslot (int /*<<< orphan*/ ,unsigned long) ; 
 unsigned long hpte_rpn (unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_memslots_raw (struct kvm*) ; 
 int /*<<< orphan*/  kvmppc_actual_pgsz (unsigned long,unsigned long) ; 
 unsigned long* real_vmalloc_addr (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned long *revmap_for_hpte(struct kvm *kvm, unsigned long hpte_v,
				      unsigned long hpte_gr,
				      struct kvm_memory_slot **memslotp,
				      unsigned long *gfnp)
{
	struct kvm_memory_slot *memslot;
	unsigned long *rmap;
	unsigned long gfn;

	gfn = hpte_rpn(hpte_gr, kvmppc_actual_pgsz(hpte_v, hpte_gr));
	memslot = __gfn_to_memslot(kvm_memslots_raw(kvm), gfn);
	if (memslotp)
		*memslotp = memslot;
	if (gfnp)
		*gfnp = gfn;
	if (!memslot)
		return NULL;

	rmap = real_vmalloc_addr(&memslot->arch.rmap[gfn - memslot->base_gfn]);
	return rmap;
}