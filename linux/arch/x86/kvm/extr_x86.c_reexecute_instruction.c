#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* mmu; } ;
struct kvm_vcpu {TYPE_4__* kvm; TYPE_2__ arch; } ;
typedef  int /*<<< orphan*/  kvm_pfn_t ;
typedef  scalar_t__ gva_t ;
typedef  scalar_t__ gpa_t ;
struct TYPE_8__ {unsigned int indirect_shadow_pages; } ;
struct TYPE_9__ {int /*<<< orphan*/  mmu_lock; TYPE_3__ arch; } ;
struct TYPE_6__ {scalar_t__ direct_map; } ;

/* Variables and functions */
 int EMULTYPE_ALLOW_RETRY ; 
 scalar_t__ UNMAPPED_GVA ; 
 scalar_t__ WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gfn_to_pfn (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpa_to_gfn (scalar_t__) ; 
 scalar_t__ is_error_noslot_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_guest_mode (struct kvm_vcpu*) ; 
 scalar_t__ kvm_mmu_gva_to_gpa_write (struct kvm_vcpu*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kvm_mmu_unprotect_page (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_release_pfn_clean (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool reexecute_instruction(struct kvm_vcpu *vcpu, gva_t cr2,
				  bool write_fault_to_shadow_pgtable,
				  int emulation_type)
{
	gpa_t gpa = cr2;
	kvm_pfn_t pfn;

	if (!(emulation_type & EMULTYPE_ALLOW_RETRY))
		return false;

	if (WARN_ON_ONCE(is_guest_mode(vcpu)))
		return false;

	if (!vcpu->arch.mmu->direct_map) {
		/*
		 * Write permission should be allowed since only
		 * write access need to be emulated.
		 */
		gpa = kvm_mmu_gva_to_gpa_write(vcpu, cr2, NULL);

		/*
		 * If the mapping is invalid in guest, let cpu retry
		 * it to generate fault.
		 */
		if (gpa == UNMAPPED_GVA)
			return true;
	}

	/*
	 * Do not retry the unhandleable instruction if it faults on the
	 * readonly host memory, otherwise it will goto a infinite loop:
	 * retry instruction -> write #PF -> emulation fail -> retry
	 * instruction -> ...
	 */
	pfn = gfn_to_pfn(vcpu->kvm, gpa_to_gfn(gpa));

	/*
	 * If the instruction failed on the error pfn, it can not be fixed,
	 * report the error to userspace.
	 */
	if (is_error_noslot_pfn(pfn))
		return false;

	kvm_release_pfn_clean(pfn);

	/* The instructions are well-emulated on direct mmu. */
	if (vcpu->arch.mmu->direct_map) {
		unsigned int indirect_shadow_pages;

		spin_lock(&vcpu->kvm->mmu_lock);
		indirect_shadow_pages = vcpu->kvm->arch.indirect_shadow_pages;
		spin_unlock(&vcpu->kvm->mmu_lock);

		if (indirect_shadow_pages)
			kvm_mmu_unprotect_page(vcpu->kvm, gpa_to_gfn(gpa));

		return true;
	}

	/*
	 * if emulation was due to access to shadowed page table
	 * and it failed try to unshadow page and re-enter the
	 * guest to let CPU execute the instruction.
	 */
	kvm_mmu_unprotect_page(vcpu->kvm, gpa_to_gfn(gpa));

	/*
	 * If the access faults on its page table, it can not
	 * be fixed by unprotecting shadow page and it should
	 * be reported to userspace.
	 */
	return !write_fault_to_shadow_pgtable;
}