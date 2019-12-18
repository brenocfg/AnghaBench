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
struct TYPE_2__ {int /*<<< orphan*/  exit_userspace; } ;
struct kvm_vcpu {TYPE_1__ stat; int /*<<< orphan*/  vcpu_id; int /*<<< orphan*/  kvm; } ;
struct kvm_run {int kvm_valid_regs; int kvm_dirty_regs; int /*<<< orphan*/  exit_reason; scalar_t__ immediate_exit; } ;

/* Variables and functions */
 int EINTR ; 
 int EINVAL ; 
 int EREMOTE ; 
 int /*<<< orphan*/  KVM_EXIT_INTR ; 
 int KVM_SYNC_S390_VALID_FIELDS ; 
 int __vcpu_run (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  disable_cpu_timer_accounting (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  enable_cpu_timer_accounting (struct kvm_vcpu*) ; 
 scalar_t__ guestdbg_exit_pending (struct kvm_vcpu*) ; 
 scalar_t__ is_vcpu_stopped (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_prepare_debug_exit (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_s390_user_cpu_state_ctrl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_s390_vcpu_start (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_sigset_activate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_sigset_deactivate (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  might_fault () ; 
 int /*<<< orphan*/  pr_err_ratelimited (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  store_regs (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  sync_regs (struct kvm_vcpu*,struct kvm_run*) ; 
 int /*<<< orphan*/  vcpu_load (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vcpu_put (struct kvm_vcpu*) ; 

int kvm_arch_vcpu_ioctl_run(struct kvm_vcpu *vcpu, struct kvm_run *kvm_run)
{
	int rc;

	if (kvm_run->immediate_exit)
		return -EINTR;

	if (kvm_run->kvm_valid_regs & ~KVM_SYNC_S390_VALID_FIELDS ||
	    kvm_run->kvm_dirty_regs & ~KVM_SYNC_S390_VALID_FIELDS)
		return -EINVAL;

	vcpu_load(vcpu);

	if (guestdbg_exit_pending(vcpu)) {
		kvm_s390_prepare_debug_exit(vcpu);
		rc = 0;
		goto out;
	}

	kvm_sigset_activate(vcpu);

	if (!kvm_s390_user_cpu_state_ctrl(vcpu->kvm)) {
		kvm_s390_vcpu_start(vcpu);
	} else if (is_vcpu_stopped(vcpu)) {
		pr_err_ratelimited("can't run stopped vcpu %d\n",
				   vcpu->vcpu_id);
		rc = -EINVAL;
		goto out;
	}

	sync_regs(vcpu, kvm_run);
	enable_cpu_timer_accounting(vcpu);

	might_fault();
	rc = __vcpu_run(vcpu);

	if (signal_pending(current) && !rc) {
		kvm_run->exit_reason = KVM_EXIT_INTR;
		rc = -EINTR;
	}

	if (guestdbg_exit_pending(vcpu) && !rc)  {
		kvm_s390_prepare_debug_exit(vcpu);
		rc = 0;
	}

	if (rc == -EREMOTE) {
		/* userspace support is needed, kvm_run has been prepared */
		rc = 0;
	}

	disable_cpu_timer_accounting(vcpu);
	store_regs(vcpu, kvm_run);

	kvm_sigset_deactivate(vcpu);

	vcpu->stat.exit_userspace++;
out:
	vcpu_put(vcpu);
	return rc;
}