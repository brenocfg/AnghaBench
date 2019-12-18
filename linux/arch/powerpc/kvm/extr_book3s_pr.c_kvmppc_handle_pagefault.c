#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ulong ;
typedef  int u64 ;
struct kvmppc_pte {int may_execute; int may_read; int may_write; int raddr; int eaddr; int vpage; int /*<<< orphan*/  wimg; int /*<<< orphan*/  page_size; int /*<<< orphan*/  member_0; } ;
struct TYPE_4__ {int (* xlate ) (struct kvm_vcpu*,int,struct kvmppc_pte*,int,int) ;scalar_t__ (* is_dcbz32 ) (struct kvm_vcpu*) ;int /*<<< orphan*/  (* esid_to_vsid ) (struct kvm_vcpu*,int,int*) ;} ;
struct TYPE_6__ {int fault_dsisr; int hflags; int paddr_accessed; int vaddr_accessed; TYPE_1__ mmu; } ;
struct TYPE_5__ {int /*<<< orphan*/  mmio_exits; int /*<<< orphan*/  sp_storage; } ;
struct kvm_vcpu {TYPE_3__ arch; TYPE_2__ stat; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int BOOK3S_HFLAG_DCBZ32 ; 
 int BOOK3S_HFLAG_SPLIT_HACK ; 
 int BOOK3S_INTERRUPT_DATA_STORAGE ; 
 int DSISR_ISSTORE ; 
 int DSISR_NOHPTE ; 
 int DSISR_PROTFAULT ; 
 int EINVAL ; 
 int /*<<< orphan*/  EIO ; 
 int ENOENT ; 
 int EPERM ; 
 int /*<<< orphan*/  HPTE_R_M ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int KVM_PAM ; 
 int /*<<< orphan*/  MMU_PAGE_64K ; 
#define  MSR_DR 129 
#define  MSR_IR 128 
 int RESUME_GUEST ; 
 int RESUME_HOST ; 
 int RESUME_HOST_NV ; 
 int SID_SHIFT ; 
 int SPLIT_HACK_MASK ; 
 int SPLIT_HACK_OFFS ; 
 int /*<<< orphan*/  VSID_REAL ; 
 int /*<<< orphan*/  VSID_REAL_DR ; 
 int /*<<< orphan*/  VSID_REAL_IR ; 
 int /*<<< orphan*/  kvmppc_book3s_queue_irqprio (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_core_queue_data_storage (struct kvm_vcpu*,int,int) ; 
 int /*<<< orphan*/  kvmppc_core_queue_inst_storage (struct kvm_vcpu*,int) ; 
 int kvmppc_emulate_mmio (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_get_fault_dar (struct kvm_vcpu*) ; 
 int const kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_mmu_map_page (struct kvm_vcpu*,struct kvmppc_pte*,int) ; 
 int /*<<< orphan*/  kvmppc_mmu_unmap_page (struct kvm_vcpu*,struct kvmppc_pte*) ; 
 int /*<<< orphan*/  kvmppc_patch_dcbz (struct kvm_vcpu*,struct kvmppc_pte*) ; 
 int /*<<< orphan*/  kvmppc_set_dar (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 scalar_t__ kvmppc_visible_gpa (struct kvm_vcpu*,int) ; 
 int stub1 (struct kvm_vcpu*,int,struct kvmppc_pte*,int,int) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*,int,int*) ; 
 scalar_t__ stub3 (struct kvm_vcpu*) ; 
 scalar_t__ stub4 (struct kvm_vcpu*) ; 

int kvmppc_handle_pagefault(struct kvm_run *run, struct kvm_vcpu *vcpu,
			    ulong eaddr, int vec)
{
	bool data = (vec == BOOK3S_INTERRUPT_DATA_STORAGE);
	bool iswrite = false;
	int r = RESUME_GUEST;
	int relocated;
	int page_found = 0;
	struct kvmppc_pte pte = { 0 };
	bool dr = (kvmppc_get_msr(vcpu) & MSR_DR) ? true : false;
	bool ir = (kvmppc_get_msr(vcpu) & MSR_IR) ? true : false;
	u64 vsid;

	relocated = data ? dr : ir;
	if (data && (vcpu->arch.fault_dsisr & DSISR_ISSTORE))
		iswrite = true;

	/* Resolve real address if translation turned on */
	if (relocated) {
		page_found = vcpu->arch.mmu.xlate(vcpu, eaddr, &pte, data, iswrite);
	} else {
		pte.may_execute = true;
		pte.may_read = true;
		pte.may_write = true;
		pte.raddr = eaddr & KVM_PAM;
		pte.eaddr = eaddr;
		pte.vpage = eaddr >> 12;
		pte.page_size = MMU_PAGE_64K;
		pte.wimg = HPTE_R_M;
	}

	switch (kvmppc_get_msr(vcpu) & (MSR_DR|MSR_IR)) {
	case 0:
		pte.vpage |= ((u64)VSID_REAL << (SID_SHIFT - 12));
		break;
	case MSR_DR:
		if (!data &&
		    (vcpu->arch.hflags & BOOK3S_HFLAG_SPLIT_HACK) &&
		    ((pte.raddr & SPLIT_HACK_MASK) == SPLIT_HACK_OFFS))
			pte.raddr &= ~SPLIT_HACK_MASK;
		/* fall through */
	case MSR_IR:
		vcpu->arch.mmu.esid_to_vsid(vcpu, eaddr >> SID_SHIFT, &vsid);

		if ((kvmppc_get_msr(vcpu) & (MSR_DR|MSR_IR)) == MSR_DR)
			pte.vpage |= ((u64)VSID_REAL_DR << (SID_SHIFT - 12));
		else
			pte.vpage |= ((u64)VSID_REAL_IR << (SID_SHIFT - 12));
		pte.vpage |= vsid;

		if (vsid == -1)
			page_found = -EINVAL;
		break;
	}

	if (vcpu->arch.mmu.is_dcbz32(vcpu) &&
	   (!(vcpu->arch.hflags & BOOK3S_HFLAG_DCBZ32))) {
		/*
		 * If we do the dcbz hack, we have to NX on every execution,
		 * so we can patch the executing code. This renders our guest
		 * NX-less.
		 */
		pte.may_execute = !data;
	}

	if (page_found == -ENOENT || page_found == -EPERM) {
		/* Page not found in guest PTE entries, or protection fault */
		u64 flags;

		if (page_found == -EPERM)
			flags = DSISR_PROTFAULT;
		else
			flags = DSISR_NOHPTE;
		if (data) {
			flags |= vcpu->arch.fault_dsisr & DSISR_ISSTORE;
			kvmppc_core_queue_data_storage(vcpu, eaddr, flags);
		} else {
			kvmppc_core_queue_inst_storage(vcpu, flags);
		}
	} else if (page_found == -EINVAL) {
		/* Page not found in guest SLB */
		kvmppc_set_dar(vcpu, kvmppc_get_fault_dar(vcpu));
		kvmppc_book3s_queue_irqprio(vcpu, vec + 0x80);
	} else if (kvmppc_visible_gpa(vcpu, pte.raddr)) {
		if (data && !(vcpu->arch.fault_dsisr & DSISR_NOHPTE)) {
			/*
			 * There is already a host HPTE there, presumably
			 * a read-only one for a page the guest thinks
			 * is writable, so get rid of it first.
			 */
			kvmppc_mmu_unmap_page(vcpu, &pte);
		}
		/* The guest's PTE is not mapped yet. Map on the host */
		if (kvmppc_mmu_map_page(vcpu, &pte, iswrite) == -EIO) {
			/* Exit KVM if mapping failed */
			run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
			return RESUME_HOST;
		}
		if (data)
			vcpu->stat.sp_storage++;
		else if (vcpu->arch.mmu.is_dcbz32(vcpu) &&
			 (!(vcpu->arch.hflags & BOOK3S_HFLAG_DCBZ32)))
			kvmppc_patch_dcbz(vcpu, &pte);
	} else {
		/* MMIO */
		vcpu->stat.mmio_exits++;
		vcpu->arch.paddr_accessed = pte.raddr;
		vcpu->arch.vaddr_accessed = pte.eaddr;
		r = kvmppc_emulate_mmio(run, vcpu);
		if ( r == RESUME_HOST_NV )
			r = RESUME_HOST;
	}

	return r;
}