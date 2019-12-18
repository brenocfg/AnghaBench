#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct revmap_entry {unsigned long guest_rpte; } ;
struct mmio_hpte_cache_entry {long pte_index; unsigned long hpte_v; unsigned long hpte_r; unsigned long rpte; unsigned long eaddr; unsigned int slb_base_pshift; unsigned long slb_v; long mmio_update; } ;
struct TYPE_7__ {int msr; } ;
struct TYPE_8__ {unsigned long pgfault_addr; long pgfault_index; unsigned long* pgfault_hpte; TYPE_3__ shregs; struct mmio_hpte_cache_entry* pgfault_cache; int /*<<< orphan*/  amr; } ;
struct kvm_vcpu {TYPE_4__ arch; struct kvm* kvm; } ;
struct TYPE_5__ {int /*<<< orphan*/ * rev; scalar_t__ virt; } ;
struct TYPE_6__ {TYPE_1__ hpt; int /*<<< orphan*/  mmio_update; } ;
struct kvm {TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  __be64 ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_FTR_ARCH_300 ; 
 unsigned int DSISR_ISSTORE ; 
 unsigned int DSISR_KEYFAULT ; 
 unsigned int DSISR_NOHPTE ; 
 unsigned int DSISR_PROTFAULT ; 
 unsigned long HPTE_R_G ; 
 unsigned long HPTE_R_KEY_HI ; 
 unsigned long HPTE_R_KEY_LO ; 
 unsigned long HPTE_R_N ; 
 unsigned long HPTE_R_PP ; 
 unsigned long HPTE_R_PP0 ; 
 unsigned long HPTE_V_ABSENT ; 
 unsigned long HPTE_V_HVLOCK ; 
 unsigned long HPTE_V_VALID ; 
 int MSR_DR ; 
 int MSR_IR ; 
 int MSR_PR ; 
 unsigned long SLB_VSID_KP ; 
 unsigned long SLB_VSID_KS ; 
 unsigned long SLB_VSID_L ; 
 unsigned long SLB_VSID_LP ; 
 unsigned int SRR1_ISI_N_OR_G ; 
 unsigned int SRR1_ISI_PROT ; 
 long atomic64_read (int /*<<< orphan*/ *) ; 
 unsigned long be64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ cpu_has_feature (int /*<<< orphan*/ ) ; 
 unsigned int hpte_get_skey_perm (unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long hpte_new_to_old_r (unsigned long) ; 
 unsigned long hpte_new_to_old_v (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  hpte_read_permission (unsigned long,unsigned long) ; 
 int /*<<< orphan*/  hpte_write_permission (unsigned long,unsigned long) ; 
 long kvmppc_hv_find_lock_hpte (struct kvm*,unsigned long,unsigned long,unsigned long) ; 
 struct mmio_hpte_cache_entry* mmio_cache_search (struct kvm_vcpu*,unsigned long,unsigned long,long) ; 
 struct mmio_hpte_cache_entry* next_mmio_cache_entry (struct kvm_vcpu*) ; 
 struct revmap_entry* real_vmalloc_addr (int /*<<< orphan*/ *) ; 
 unsigned int* slb_base_page_shift ; 
 int /*<<< orphan*/  unlock_hpte (int /*<<< orphan*/ *,unsigned long) ; 

long kvmppc_hpte_hv_fault(struct kvm_vcpu *vcpu, unsigned long addr,
			  unsigned long slb_v, unsigned int status, bool data)
{
	struct kvm *kvm = vcpu->kvm;
	long int index;
	unsigned long v, r, gr, orig_v;
	__be64 *hpte;
	unsigned long valid;
	struct revmap_entry *rev;
	unsigned long pp, key;
	struct mmio_hpte_cache_entry *cache_entry = NULL;
	long mmio_update = 0;

	/* For protection fault, expect to find a valid HPTE */
	valid = HPTE_V_VALID;
	if (status & DSISR_NOHPTE) {
		valid |= HPTE_V_ABSENT;
		mmio_update = atomic64_read(&kvm->arch.mmio_update);
		cache_entry = mmio_cache_search(vcpu, addr, slb_v, mmio_update);
	}
	if (cache_entry) {
		index = cache_entry->pte_index;
		v = cache_entry->hpte_v;
		r = cache_entry->hpte_r;
		gr = cache_entry->rpte;
	} else {
		index = kvmppc_hv_find_lock_hpte(kvm, addr, slb_v, valid);
		if (index < 0) {
			if (status & DSISR_NOHPTE)
				return status;	/* there really was no HPTE */
			return 0;	/* for prot fault, HPTE disappeared */
		}
		hpte = (__be64 *)(kvm->arch.hpt.virt + (index << 4));
		v = orig_v = be64_to_cpu(hpte[0]) & ~HPTE_V_HVLOCK;
		r = be64_to_cpu(hpte[1]);
		if (cpu_has_feature(CPU_FTR_ARCH_300)) {
			v = hpte_new_to_old_v(v, r);
			r = hpte_new_to_old_r(r);
		}
		rev = real_vmalloc_addr(&kvm->arch.hpt.rev[index]);
		gr = rev->guest_rpte;

		unlock_hpte(hpte, orig_v);
	}

	/* For not found, if the HPTE is valid by now, retry the instruction */
	if ((status & DSISR_NOHPTE) && (v & HPTE_V_VALID))
		return 0;

	/* Check access permissions to the page */
	pp = gr & (HPTE_R_PP0 | HPTE_R_PP);
	key = (vcpu->arch.shregs.msr & MSR_PR) ? SLB_VSID_KP : SLB_VSID_KS;
	status &= ~DSISR_NOHPTE;	/* DSISR_NOHPTE == SRR1_ISI_NOPT */
	if (!data) {
		if (gr & (HPTE_R_N | HPTE_R_G))
			return status | SRR1_ISI_N_OR_G;
		if (!hpte_read_permission(pp, slb_v & key))
			return status | SRR1_ISI_PROT;
	} else if (status & DSISR_ISSTORE) {
		/* check write permission */
		if (!hpte_write_permission(pp, slb_v & key))
			return status | DSISR_PROTFAULT;
	} else {
		if (!hpte_read_permission(pp, slb_v & key))
			return status | DSISR_PROTFAULT;
	}

	/* Check storage key, if applicable */
	if (data && (vcpu->arch.shregs.msr & MSR_DR)) {
		unsigned int perm = hpte_get_skey_perm(gr, vcpu->arch.amr);
		if (status & DSISR_ISSTORE)
			perm >>= 1;
		if (perm & 1)
			return status | DSISR_KEYFAULT;
	}

	/* Save HPTE info for virtual-mode handler */
	vcpu->arch.pgfault_addr = addr;
	vcpu->arch.pgfault_index = index;
	vcpu->arch.pgfault_hpte[0] = v;
	vcpu->arch.pgfault_hpte[1] = r;
	vcpu->arch.pgfault_cache = cache_entry;

	/* Check the storage key to see if it is possibly emulated MMIO */
	if ((r & (HPTE_R_KEY_HI | HPTE_R_KEY_LO)) ==
	    (HPTE_R_KEY_HI | HPTE_R_KEY_LO)) {
		if (!cache_entry) {
			unsigned int pshift = 12;
			unsigned int pshift_index;

			if (slb_v & SLB_VSID_L) {
				pshift_index = ((slb_v & SLB_VSID_LP) >> 4);
				pshift = slb_base_page_shift[pshift_index];
			}
			cache_entry = next_mmio_cache_entry(vcpu);
			cache_entry->eaddr = addr;
			cache_entry->slb_base_pshift = pshift;
			cache_entry->pte_index = index;
			cache_entry->hpte_v = v;
			cache_entry->hpte_r = r;
			cache_entry->rpte = gr;
			cache_entry->slb_v = slb_v;
			cache_entry->mmio_update = mmio_update;
		}
		if (data && (vcpu->arch.shregs.msr & MSR_IR))
			return -2;	/* MMIO emulation - load instr word */
	}

	return -1;		/* send fault up to host kernel mode */
}