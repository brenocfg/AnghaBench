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
typedef  int /*<<< orphan*/  vrsave ;
struct TYPE_2__ {int /*<<< orphan*/  sane; } ;
struct kvm_vcpu {int /*<<< orphan*/  mode; TYPE_1__ arch; } ;
struct kvm_run {int /*<<< orphan*/  exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  BOOK3S_INTERRUPT_FP_UNAVAIL ; 
 int EINVAL ; 
 int /*<<< orphan*/  FSCR_TAR_LG ; 
 int /*<<< orphan*/  KVM_EXIT_INTERNAL_ERROR ; 
 int MSR_FP ; 
 int MSR_VEC ; 
 int MSR_VSX ; 
 int /*<<< orphan*/  OUTSIDE_GUEST_MODE ; 
 int __kvmppc_vcpu_run (struct kvm_run*,struct kvm_vcpu*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  giveup_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_clear_debug (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_fix_ee_before_entry () ; 
 int kvmppc_get_msr (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_giveup_ext (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  kvmppc_giveup_fac (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvmppc_handle_ext (struct kvm_vcpu*,int /*<<< orphan*/ ,int) ; 
 int kvmppc_prepare_to_enter (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvmppc_setup_debug (struct kvm_vcpu*) ; 

__attribute__((used)) static int kvmppc_vcpu_run_pr(struct kvm_run *kvm_run, struct kvm_vcpu *vcpu)
{
	int ret;
#ifdef CONFIG_ALTIVEC
	unsigned long uninitialized_var(vrsave);
#endif

	/* Check if we can run the vcpu at all */
	if (!vcpu->arch.sane) {
		kvm_run->exit_reason = KVM_EXIT_INTERNAL_ERROR;
		ret = -EINVAL;
		goto out;
	}

	kvmppc_setup_debug(vcpu);

	/*
	 * Interrupts could be timers for the guest which we have to inject
	 * again, so let's postpone them until we're in the guest and if we
	 * really did time things so badly, then we just exit again due to
	 * a host external interrupt.
	 */
	ret = kvmppc_prepare_to_enter(vcpu);
	if (ret <= 0)
		goto out;
	/* interrupts now hard-disabled */

	/* Save FPU, Altivec and VSX state */
	giveup_all(current);

	/* Preload FPU if it's enabled */
	if (kvmppc_get_msr(vcpu) & MSR_FP)
		kvmppc_handle_ext(vcpu, BOOK3S_INTERRUPT_FP_UNAVAIL, MSR_FP);

	kvmppc_fix_ee_before_entry();

	ret = __kvmppc_vcpu_run(kvm_run, vcpu);

	kvmppc_clear_debug(vcpu);

	/* No need for guest_exit. It's done in handle_exit.
	   We also get here with interrupts enabled. */

	/* Make sure we save the guest FPU/Altivec/VSX state */
	kvmppc_giveup_ext(vcpu, MSR_FP | MSR_VEC | MSR_VSX);

	/* Make sure we save the guest TAR/EBB/DSCR state */
	kvmppc_giveup_fac(vcpu, FSCR_TAR_LG);

out:
	vcpu->mode = OUTSIDE_GUEST_MODE;
	return ret;
}