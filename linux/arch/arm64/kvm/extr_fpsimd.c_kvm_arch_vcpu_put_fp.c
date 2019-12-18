#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct TYPE_4__ {int /*<<< orphan*/ * sys_regs; } ;
struct TYPE_3__ {int flags; TYPE_2__ ctxt; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPACR_EL1 ; 
 int /*<<< orphan*/  CPACR_EL1_ZEN_EL0EN ; 
 int KVM_ARM64_FP_ENABLED ; 
 int KVM_ARM64_HOST_SVE_ENABLED ; 
 int KVM_ARM64_HOST_SVE_IN_USE ; 
 int /*<<< orphan*/  SYS_ZCR_EL12 ; 
 int /*<<< orphan*/  TIF_SVE ; 
 size_t ZCR_EL1 ; 
 int /*<<< orphan*/  fpsimd_save_and_flush_cpu_state () ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  read_sysreg_s (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysreg_clear_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int system_supports_sve () ; 
 int /*<<< orphan*/  update_thread_flag (int /*<<< orphan*/ ,int) ; 
 int vcpu_has_sve (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_put_fp(struct kvm_vcpu *vcpu)
{
	unsigned long flags;
	bool host_has_sve = system_supports_sve();
	bool guest_has_sve = vcpu_has_sve(vcpu);

	local_irq_save(flags);

	if (vcpu->arch.flags & KVM_ARM64_FP_ENABLED) {
		u64 *guest_zcr = &vcpu->arch.ctxt.sys_regs[ZCR_EL1];

		fpsimd_save_and_flush_cpu_state();

		if (guest_has_sve)
			*guest_zcr = read_sysreg_s(SYS_ZCR_EL12);
	} else if (host_has_sve) {
		/*
		 * The FPSIMD/SVE state in the CPU has not been touched, and we
		 * have SVE (and VHE): CPACR_EL1 (alias CPTR_EL2) has been
		 * reset to CPACR_EL1_DEFAULT by the Hyp code, disabling SVE
		 * for EL0.  To avoid spurious traps, restore the trap state
		 * seen by kvm_arch_vcpu_load_fp():
		 */
		if (vcpu->arch.flags & KVM_ARM64_HOST_SVE_ENABLED)
			sysreg_clear_set(CPACR_EL1, 0, CPACR_EL1_ZEN_EL0EN);
		else
			sysreg_clear_set(CPACR_EL1, CPACR_EL1_ZEN_EL0EN, 0);
	}

	update_thread_flag(TIF_SVE,
			   vcpu->arch.flags & KVM_ARM64_HOST_SVE_IN_USE);

	local_irq_restore(flags);
}