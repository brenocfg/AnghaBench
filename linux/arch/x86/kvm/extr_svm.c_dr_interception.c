#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  switch_db_regs; } ;
struct TYPE_13__ {scalar_t__ guest_debug; TYPE_1__ arch; } ;
struct vcpu_svm {TYPE_4__ vcpu; TYPE_3__* vmcb; } ;
struct TYPE_11__ {int exit_info_1; int exit_code; } ;
struct TYPE_12__ {TYPE_2__ control; } ;

/* Variables and functions */
 int /*<<< orphan*/  KVM_DEBUGREG_WONT_EXIT ; 
 int SVM_EXITINFO_REG_MASK ; 
 int SVM_EXIT_READ_DR0 ; 
 int /*<<< orphan*/  X86_FEATURE_DECODEASSISTS ; 
 int /*<<< orphan*/  boot_cpu_has (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  clr_dr_intercepts (struct vcpu_svm*) ; 
 int emulate_on_interception (struct vcpu_svm*) ; 
 int /*<<< orphan*/  kvm_get_dr (TYPE_4__*,int,unsigned long*) ; 
 unsigned long kvm_register_read (TYPE_4__*,int) ; 
 int /*<<< orphan*/  kvm_register_write (TYPE_4__*,int,unsigned long) ; 
 int /*<<< orphan*/  kvm_require_dr (TYPE_4__*,int) ; 
 int /*<<< orphan*/  kvm_set_dr (TYPE_4__*,int,unsigned long) ; 
 int kvm_skip_emulated_instruction (TYPE_4__*) ; 

__attribute__((used)) static int dr_interception(struct vcpu_svm *svm)
{
	int reg, dr;
	unsigned long val;

	if (svm->vcpu.guest_debug == 0) {
		/*
		 * No more DR vmexits; force a reload of the debug registers
		 * and reenter on this instruction.  The next vmexit will
		 * retrieve the full state of the debug registers.
		 */
		clr_dr_intercepts(svm);
		svm->vcpu.arch.switch_db_regs |= KVM_DEBUGREG_WONT_EXIT;
		return 1;
	}

	if (!boot_cpu_has(X86_FEATURE_DECODEASSISTS))
		return emulate_on_interception(svm);

	reg = svm->vmcb->control.exit_info_1 & SVM_EXITINFO_REG_MASK;
	dr = svm->vmcb->control.exit_code - SVM_EXIT_READ_DR0;

	if (dr >= 16) { /* mov to DRn */
		if (!kvm_require_dr(&svm->vcpu, dr - 16))
			return 1;
		val = kvm_register_read(&svm->vcpu, reg);
		kvm_set_dr(&svm->vcpu, dr - 16, val);
	} else {
		if (!kvm_require_dr(&svm->vcpu, dr))
			return 1;
		kvm_get_dr(&svm->vcpu, dr, &val);
		kvm_register_write(&svm->vcpu, reg, val);
	}

	return kvm_skip_emulated_instruction(&svm->vcpu);
}