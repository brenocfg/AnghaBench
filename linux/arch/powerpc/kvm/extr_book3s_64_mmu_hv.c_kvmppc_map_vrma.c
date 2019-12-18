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
struct kvm_vcpu {struct kvm* kvm; } ;
struct kvm_memory_slot {unsigned long npages; } ;
struct TYPE_2__ {int /*<<< orphan*/  hpt; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 unsigned long HPTE_R_C ; 
 unsigned long HPTE_R_M ; 
 unsigned long HPTE_R_R ; 
 int HPTE_V_1TB_SEG ; 
 int HPTE_V_BOLTED ; 
 int /*<<< orphan*/  H_EXACT ; 
 long H_SUCCESS ; 
 unsigned long PAGE_SHIFT ; 
 unsigned long PP_RWXX ; 
 int VRMA_VSID ; 
 int hpte0_pgsize_encoding (unsigned long) ; 
 unsigned long hpte1_pgsize_encoding (unsigned long) ; 
 unsigned long kvmppc_hpt_mask (int /*<<< orphan*/ *) ; 
 long kvmppc_virtmode_do_h_enter (struct kvm*,int /*<<< orphan*/ ,unsigned long,unsigned long,unsigned long,unsigned long*) ; 
 int /*<<< orphan*/  pr_err (char*,unsigned long,long) ; 

void kvmppc_map_vrma(struct kvm_vcpu *vcpu, struct kvm_memory_slot *memslot,
		     unsigned long porder)
{
	unsigned long i;
	unsigned long npages;
	unsigned long hp_v, hp_r;
	unsigned long addr, hash;
	unsigned long psize;
	unsigned long hp0, hp1;
	unsigned long idx_ret;
	long ret;
	struct kvm *kvm = vcpu->kvm;

	psize = 1ul << porder;
	npages = memslot->npages >> (porder - PAGE_SHIFT);

	/* VRMA can't be > 1TB */
	if (npages > 1ul << (40 - porder))
		npages = 1ul << (40 - porder);
	/* Can't use more than 1 HPTE per HPTEG */
	if (npages > kvmppc_hpt_mask(&kvm->arch.hpt) + 1)
		npages = kvmppc_hpt_mask(&kvm->arch.hpt) + 1;

	hp0 = HPTE_V_1TB_SEG | (VRMA_VSID << (40 - 16)) |
		HPTE_V_BOLTED | hpte0_pgsize_encoding(psize);
	hp1 = hpte1_pgsize_encoding(psize) |
		HPTE_R_R | HPTE_R_C | HPTE_R_M | PP_RWXX;

	for (i = 0; i < npages; ++i) {
		addr = i << porder;
		/* can't use hpt_hash since va > 64 bits */
		hash = (i ^ (VRMA_VSID ^ (VRMA_VSID << 25)))
			& kvmppc_hpt_mask(&kvm->arch.hpt);
		/*
		 * We assume that the hash table is empty and no
		 * vcpus are using it at this stage.  Since we create
		 * at most one HPTE per HPTEG, we just assume entry 7
		 * is available and use it.
		 */
		hash = (hash << 3) + 7;
		hp_v = hp0 | ((addr >> 16) & ~0x7fUL);
		hp_r = hp1 | addr;
		ret = kvmppc_virtmode_do_h_enter(kvm, H_EXACT, hash, hp_v, hp_r,
						 &idx_ret);
		if (ret != H_SUCCESS) {
			pr_err("KVM: map_vrma at %lx failed, ret=%ld\n",
			       addr, ret);
			break;
		}
	}
}