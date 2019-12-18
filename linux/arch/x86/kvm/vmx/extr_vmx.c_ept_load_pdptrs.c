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
struct TYPE_2__ {int /*<<< orphan*/  regs_dirty; struct kvm_mmu* walk_mmu; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;
struct kvm_mmu {int /*<<< orphan*/ * pdptrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GUEST_PDPTR0 ; 
 int /*<<< orphan*/  GUEST_PDPTR1 ; 
 int /*<<< orphan*/  GUEST_PDPTR2 ; 
 int /*<<< orphan*/  GUEST_PDPTR3 ; 
 int /*<<< orphan*/  VCPU_EXREG_PDPTR ; 
 scalar_t__ is_pae_paging (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,unsigned long*) ; 
 int /*<<< orphan*/  vmcs_write64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ept_load_pdptrs(struct kvm_vcpu *vcpu)
{
	struct kvm_mmu *mmu = vcpu->arch.walk_mmu;

	if (!test_bit(VCPU_EXREG_PDPTR,
		      (unsigned long *)&vcpu->arch.regs_dirty))
		return;

	if (is_pae_paging(vcpu)) {
		vmcs_write64(GUEST_PDPTR0, mmu->pdptrs[0]);
		vmcs_write64(GUEST_PDPTR1, mmu->pdptrs[1]);
		vmcs_write64(GUEST_PDPTR2, mmu->pdptrs[2]);
		vmcs_write64(GUEST_PDPTR3, mmu->pdptrs[3]);
	}
}