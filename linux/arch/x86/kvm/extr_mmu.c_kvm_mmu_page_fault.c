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
typedef  int u64 ;
struct TYPE_5__ {int gpa_available; TYPE_1__* mmu; int /*<<< orphan*/  gpa_val; } ;
struct kvm_vcpu {int /*<<< orphan*/  kvm; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  gva_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* need_emulation_on_page_fault ) (struct kvm_vcpu*) ;} ;
struct TYPE_4__ {int direct_map; int (* page_fault ) (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int EMULTYPE_ALLOW_RETRY ; 
 int PFERR_NESTED_GUEST_PAGE ; 
 int PFERR_RSVD_MASK ; 
 int RET_PF_EMULATE ; 
 int RET_PF_INVALID ; 
 int RET_PF_RETRY ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  gpa_to_gfn (int /*<<< orphan*/ ) ; 
 int handle_mmio_page_fault (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_mmu_unprotect_page (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* kvm_x86_ops ; 
 int /*<<< orphan*/  lower_32_bits (int) ; 
 int /*<<< orphan*/  mmio_info_in_cache (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int stub1 (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub2 (struct kvm_vcpu*) ; 
 scalar_t__ unlikely (int) ; 
 int x86_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ,int,void*,int) ; 

int kvm_mmu_page_fault(struct kvm_vcpu *vcpu, gva_t cr2, u64 error_code,
		       void *insn, int insn_len)
{
	int r, emulation_type = 0;
	bool direct = vcpu->arch.mmu->direct_map;

	/* With shadow page tables, fault_address contains a GVA or nGPA.  */
	if (vcpu->arch.mmu->direct_map) {
		vcpu->arch.gpa_available = true;
		vcpu->arch.gpa_val = cr2;
	}

	r = RET_PF_INVALID;
	if (unlikely(error_code & PFERR_RSVD_MASK)) {
		r = handle_mmio_page_fault(vcpu, cr2, direct);
		if (r == RET_PF_EMULATE)
			goto emulate;
	}

	if (r == RET_PF_INVALID) {
		r = vcpu->arch.mmu->page_fault(vcpu, cr2,
					       lower_32_bits(error_code),
					       false);
		WARN_ON(r == RET_PF_INVALID);
	}

	if (r == RET_PF_RETRY)
		return 1;
	if (r < 0)
		return r;

	/*
	 * Before emulating the instruction, check if the error code
	 * was due to a RO violation while translating the guest page.
	 * This can occur when using nested virtualization with nested
	 * paging in both guests. If true, we simply unprotect the page
	 * and resume the guest.
	 */
	if (vcpu->arch.mmu->direct_map &&
	    (error_code & PFERR_NESTED_GUEST_PAGE) == PFERR_NESTED_GUEST_PAGE) {
		kvm_mmu_unprotect_page(vcpu->kvm, gpa_to_gfn(cr2));
		return 1;
	}

	/*
	 * vcpu->arch.mmu.page_fault returned RET_PF_EMULATE, but we can still
	 * optimistically try to just unprotect the page and let the processor
	 * re-execute the instruction that caused the page fault.  Do not allow
	 * retrying MMIO emulation, as it's not only pointless but could also
	 * cause us to enter an infinite loop because the processor will keep
	 * faulting on the non-existent MMIO address.  Retrying an instruction
	 * from a nested guest is also pointless and dangerous as we are only
	 * explicitly shadowing L1's page tables, i.e. unprotecting something
	 * for L1 isn't going to magically fix whatever issue cause L2 to fail.
	 */
	if (!mmio_info_in_cache(vcpu, cr2, direct) && !is_guest_mode(vcpu))
		emulation_type = EMULTYPE_ALLOW_RETRY;
emulate:
	/*
	 * On AMD platforms, under certain conditions insn_len may be zero on #NPF.
	 * This can happen if a guest gets a page-fault on data access but the HW
	 * table walker is not able to read the instruction page (e.g instruction
	 * page is not present in memory). In those cases we simply restart the
	 * guest, with the exception of AMD Erratum 1096 which is unrecoverable.
	 */
	if (unlikely(insn && !insn_len)) {
		if (!kvm_x86_ops->need_emulation_on_page_fault(vcpu))
			return 1;
	}

	return x86_emulate_instruction(vcpu, cr2, emulation_type, insn,
				       insn_len);
}