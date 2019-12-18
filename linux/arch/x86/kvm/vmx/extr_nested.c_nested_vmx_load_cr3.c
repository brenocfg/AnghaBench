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
typedef  int /*<<< orphan*/  ulong ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {unsigned long cr3; int /*<<< orphan*/  regs_avail; int /*<<< orphan*/  walk_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 scalar_t__ CC (int) ; 
 int EINVAL ; 
 int /*<<< orphan*/  ENTRY_FAIL_DEFAULT ; 
 int /*<<< orphan*/  ENTRY_FAIL_PDPTE ; 
 int /*<<< orphan*/  VCPU_EXREG_CR3 ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ is_pae_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_init_mmu (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvm_mmu_new_cr3 (struct kvm_vcpu*,unsigned long,int) ; 
 unsigned long kvm_read_cr3 (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  load_pdptrs (struct kvm_vcpu*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  nested_cr3_valid (struct kvm_vcpu*,unsigned long) ; 
 scalar_t__ pdptrs_changed (struct kvm_vcpu*) ; 

__attribute__((used)) static int nested_vmx_load_cr3(struct kvm_vcpu *vcpu, unsigned long cr3, bool nested_ept,
			       u32 *entry_failure_code)
{
	if (cr3 != kvm_read_cr3(vcpu) || (!nested_ept && pdptrs_changed(vcpu))) {
		if (CC(!nested_cr3_valid(vcpu, cr3))) {
			*entry_failure_code = ENTRY_FAIL_DEFAULT;
			return -EINVAL;
		}

		/*
		 * If PAE paging and EPT are both on, CR3 is not used by the CPU and
		 * must not be dereferenced.
		 */
		if (is_pae_paging(vcpu) && !nested_ept) {
			if (CC(!load_pdptrs(vcpu, vcpu->arch.walk_mmu, cr3))) {
				*entry_failure_code = ENTRY_FAIL_PDPTE;
				return -EINVAL;
			}
		}
	}

	if (!nested_ept)
		kvm_mmu_new_cr3(vcpu, cr3, false);

	vcpu->arch.cr3 = cr3;
	__set_bit(VCPU_EXREG_CR3, (ulong *)&vcpu->arch.regs_avail);

	kvm_init_mmu(vcpu, false);

	return 0;
}