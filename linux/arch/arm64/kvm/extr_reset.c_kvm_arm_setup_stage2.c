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
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
struct TYPE_2__ {int vtcr; } ;
struct kvm {TYPE_1__ arch; } ;

/* Variables and functions */
 int EINVAL ; 
 int ID_AA64MMFR0_PARANGE_MAX ; 
 int KVM_PHYS_SHIFT ; 
 int KVM_VM_TYPE_ARM_IPA_SIZE (unsigned long) ; 
 unsigned long KVM_VM_TYPE_ARM_IPA_SIZE_MASK ; 
 int /*<<< orphan*/  SYS_ID_AA64MMFR0_EL1 ; 
 int VTCR_EL2_FLAGS ; 
 int VTCR_EL2_HA ; 
 int VTCR_EL2_LVLS_TO_SL0 (int) ; 
 int VTCR_EL2_PS_SHIFT ; 
 int VTCR_EL2_T0SZ (int) ; 
 int VTCR_EL2_VS_16BIT ; 
 int VTCR_EL2_VS_8BIT ; 
 int kvm_get_vmid_bits () ; 
 int kvm_ipa_limit ; 
 int read_sanitised_ftr_reg (int /*<<< orphan*/ ) ; 
 int stage2_pgtable_levels (int) ; 

int kvm_arm_setup_stage2(struct kvm *kvm, unsigned long type)
{
	u64 vtcr = VTCR_EL2_FLAGS;
	u32 parange, phys_shift;
	u8 lvls;

	if (type & ~KVM_VM_TYPE_ARM_IPA_SIZE_MASK)
		return -EINVAL;

	phys_shift = KVM_VM_TYPE_ARM_IPA_SIZE(type);
	if (phys_shift) {
		if (phys_shift > kvm_ipa_limit ||
		    phys_shift < 32)
			return -EINVAL;
	} else {
		phys_shift = KVM_PHYS_SHIFT;
	}

	parange = read_sanitised_ftr_reg(SYS_ID_AA64MMFR0_EL1) & 7;
	if (parange > ID_AA64MMFR0_PARANGE_MAX)
		parange = ID_AA64MMFR0_PARANGE_MAX;
	vtcr |= parange << VTCR_EL2_PS_SHIFT;

	vtcr |= VTCR_EL2_T0SZ(phys_shift);
	/*
	 * Use a minimum 2 level page table to prevent splitting
	 * host PMD huge pages at stage2.
	 */
	lvls = stage2_pgtable_levels(phys_shift);
	if (lvls < 2)
		lvls = 2;
	vtcr |= VTCR_EL2_LVLS_TO_SL0(lvls);

	/*
	 * Enable the Hardware Access Flag management, unconditionally
	 * on all CPUs. The features is RES0 on CPUs without the support
	 * and must be ignored by the CPUs.
	 */
	vtcr |= VTCR_EL2_HA;

	/* Set the vmid bits */
	vtcr |= (kvm_get_vmid_bits() == 16) ?
		VTCR_EL2_VS_16BIT :
		VTCR_EL2_VS_8BIT;
	kvm->arch.vtcr = vtcr;
	return 0;
}