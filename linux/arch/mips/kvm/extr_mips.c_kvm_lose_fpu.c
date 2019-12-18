#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int aux_inuse; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_KVM_MIPS_VZ ; 
 int /*<<< orphan*/  IS_ENABLED (int /*<<< orphan*/ ) ; 
 int KVM_MIPS_AUX_FPU ; 
 int KVM_MIPS_AUX_MSA ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_FPU ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_FPU_MSA ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_SAVE ; 
 int /*<<< orphan*/  MIPS_CONF5_MSAEN ; 
 int ST0_CU1 ; 
 int ST0_FR ; 
 int /*<<< orphan*/  __kvm_save_fpu (TYPE_1__*) ; 
 int /*<<< orphan*/  __kvm_save_msa (TYPE_1__*) ; 
 int /*<<< orphan*/  clear_c0_status (int) ; 
 scalar_t__ cpu_has_msa ; 
 int /*<<< orphan*/  disable_fpu_hazard () ; 
 int /*<<< orphan*/  disable_msa () ; 
 int /*<<< orphan*/  enable_fpu_hazard () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  set_c0_config5 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_c0_status (int) ; 
 int /*<<< orphan*/  trace_kvm_aux (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_lose_fpu(struct kvm_vcpu *vcpu)
{
	/*
	 * With T&E, FPU & MSA get disabled in root context (hardware) when it
	 * is disabled in guest context (software), but the register state in
	 * the hardware may still be in use.
	 * This is why we explicitly re-enable the hardware before saving.
	 */

	preempt_disable();
	if (cpu_has_msa && vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA) {
		if (!IS_ENABLED(CONFIG_KVM_MIPS_VZ)) {
			set_c0_config5(MIPS_CONF5_MSAEN);
			enable_fpu_hazard();
		}

		__kvm_save_msa(&vcpu->arch);
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_SAVE, KVM_TRACE_AUX_FPU_MSA);

		/* Disable MSA & FPU */
		disable_msa();
		if (vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU) {
			clear_c0_status(ST0_CU1 | ST0_FR);
			disable_fpu_hazard();
		}
		vcpu->arch.aux_inuse &= ~(KVM_MIPS_AUX_FPU | KVM_MIPS_AUX_MSA);
	} else if (vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU) {
		if (!IS_ENABLED(CONFIG_KVM_MIPS_VZ)) {
			set_c0_status(ST0_CU1);
			enable_fpu_hazard();
		}

		__kvm_save_fpu(&vcpu->arch);
		vcpu->arch.aux_inuse &= ~KVM_MIPS_AUX_FPU;
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_SAVE, KVM_TRACE_AUX_FPU);

		/* Disable FPU */
		clear_c0_status(ST0_CU1 | ST0_FR);
		disable_fpu_hazard();
	}
	preempt_enable();
}