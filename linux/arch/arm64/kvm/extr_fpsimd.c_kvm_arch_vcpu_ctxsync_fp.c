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
struct TYPE_4__ {int /*<<< orphan*/  fp_regs; } ;
struct TYPE_5__ {TYPE_1__ gp_regs; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  sve_max_vl; int /*<<< orphan*/  sve_state; TYPE_2__ ctxt; } ;
struct kvm_vcpu {TYPE_3__ arch; } ;

/* Variables and functions */
 int KVM_ARM64_FP_ENABLED ; 
 int /*<<< orphan*/  TIF_FOREIGN_FPSTATE ; 
 int /*<<< orphan*/  TIF_SVE ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clear_thread_flag (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fpsimd_bind_state_to_cpu (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  update_thread_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_has_sve (struct kvm_vcpu*) ; 

void kvm_arch_vcpu_ctxsync_fp(struct kvm_vcpu *vcpu)
{
	WARN_ON_ONCE(!irqs_disabled());

	if (vcpu->arch.flags & KVM_ARM64_FP_ENABLED) {
		fpsimd_bind_state_to_cpu(&vcpu->arch.ctxt.gp_regs.fp_regs,
					 vcpu->arch.sve_state,
					 vcpu->arch.sve_max_vl);

		clear_thread_flag(TIF_FOREIGN_FPSTATE);
		update_thread_flag(TIF_SVE, vcpu_has_sve(vcpu));
	}
}