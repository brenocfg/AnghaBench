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
struct TYPE_3__ {int pause_in_guest; } ;
struct kvm {TYPE_1__ arch; } ;
struct TYPE_4__ {int /*<<< orphan*/  ept_pointer_lock; } ;

/* Variables and functions */
#define  L1TF_MITIGATION_FLUSH 133 
#define  L1TF_MITIGATION_FLUSH_NOSMT 132 
#define  L1TF_MITIGATION_FLUSH_NOWARN 131 
#define  L1TF_MITIGATION_FULL 130 
#define  L1TF_MITIGATION_FULL_FORCE 129 
#define  L1TF_MITIGATION_OFF 128 
 int /*<<< orphan*/  L1TF_MSG_L1D ; 
 int /*<<< orphan*/  L1TF_MSG_SMT ; 
 int /*<<< orphan*/  VMENTER_L1D_FLUSH_NEVER ; 
 int /*<<< orphan*/  X86_BUG_L1TF ; 
 scalar_t__ boot_cpu_has (int /*<<< orphan*/ ) ; 
 scalar_t__ enable_ept ; 
 int l1tf_mitigation ; 
 int /*<<< orphan*/  l1tf_vmx_mitigation ; 
 int /*<<< orphan*/  ple_gap ; 
 int /*<<< orphan*/  pr_warn_once (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_smt_active () ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 TYPE_2__* to_kvm_vmx (struct kvm*) ; 

__attribute__((used)) static int vmx_vm_init(struct kvm *kvm)
{
	spin_lock_init(&to_kvm_vmx(kvm)->ept_pointer_lock);

	if (!ple_gap)
		kvm->arch.pause_in_guest = true;

	if (boot_cpu_has(X86_BUG_L1TF) && enable_ept) {
		switch (l1tf_mitigation) {
		case L1TF_MITIGATION_OFF:
		case L1TF_MITIGATION_FLUSH_NOWARN:
			/* 'I explicitly don't care' is set */
			break;
		case L1TF_MITIGATION_FLUSH:
		case L1TF_MITIGATION_FLUSH_NOSMT:
		case L1TF_MITIGATION_FULL:
			/*
			 * Warn upon starting the first VM in a potentially
			 * insecure environment.
			 */
			if (sched_smt_active())
				pr_warn_once(L1TF_MSG_SMT);
			if (l1tf_vmx_mitigation == VMENTER_L1D_FLUSH_NEVER)
				pr_warn_once(L1TF_MSG_L1D);
			break;
		case L1TF_MITIGATION_FULL_FORCE:
			/* Flush is enforced */
			break;
		}
	}
	return 0;
}