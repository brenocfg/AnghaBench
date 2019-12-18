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
struct TYPE_2__ {int aux_inuse; } ;
struct kvm_vcpu {TYPE_1__ arch; } ;

/* Variables and functions */
 int KVM_MIPS_AUX_FPU ; 
 int KVM_MIPS_AUX_MSA ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_DISCARD ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_FPU ; 
 int /*<<< orphan*/  KVM_TRACE_AUX_MSA ; 
 int ST0_CU1 ; 
 int ST0_FR ; 
 int /*<<< orphan*/  clear_c0_status (int) ; 
 scalar_t__ cpu_has_msa ; 
 int /*<<< orphan*/  disable_msa () ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 int /*<<< orphan*/  trace_kvm_aux (struct kvm_vcpu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void kvm_drop_fpu(struct kvm_vcpu *vcpu)
{
	preempt_disable();
	if (cpu_has_msa && vcpu->arch.aux_inuse & KVM_MIPS_AUX_MSA) {
		disable_msa();
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_DISCARD, KVM_TRACE_AUX_MSA);
		vcpu->arch.aux_inuse &= ~KVM_MIPS_AUX_MSA;
	}
	if (vcpu->arch.aux_inuse & KVM_MIPS_AUX_FPU) {
		clear_c0_status(ST0_CU1 | ST0_FR);
		trace_kvm_aux(vcpu, KVM_TRACE_AUX_DISCARD, KVM_TRACE_AUX_FPU);
		vcpu->arch.aux_inuse &= ~KVM_MIPS_AUX_FPU;
	}
	preempt_enable();
}