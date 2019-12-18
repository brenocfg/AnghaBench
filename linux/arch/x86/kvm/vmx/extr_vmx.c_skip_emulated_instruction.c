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
struct kvm_vcpu {int dummy; } ;
struct TYPE_2__ {scalar_t__ exit_reason; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMULTYPE_SKIP ; 
 scalar_t__ EXIT_REASON_EPT_MISCONFIG ; 
 int /*<<< orphan*/  VM_EXIT_INSTRUCTION_LEN ; 
 int /*<<< orphan*/  X86_FEATURE_HYPERVISOR ; 
 int /*<<< orphan*/  kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 unsigned long kvm_rip_read (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  kvm_rip_write (struct kvm_vcpu*,unsigned long) ; 
 int /*<<< orphan*/  static_cpu_has (int /*<<< orphan*/ ) ; 
 TYPE_1__* to_vmx (struct kvm_vcpu*) ; 
 scalar_t__ vmcs_read32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmx_set_interrupt_shadow (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int skip_emulated_instruction(struct kvm_vcpu *vcpu)
{
	unsigned long rip;

	/*
	 * Using VMCS.VM_EXIT_INSTRUCTION_LEN on EPT misconfig depends on
	 * undefined behavior: Intel's SDM doesn't mandate the VMCS field be
	 * set when EPT misconfig occurs.  In practice, real hardware updates
	 * VM_EXIT_INSTRUCTION_LEN on EPT misconfig, but other hypervisors
	 * (namely Hyper-V) don't set it due to it being undefined behavior,
	 * i.e. we end up advancing IP with some random value.
	 */
	if (!static_cpu_has(X86_FEATURE_HYPERVISOR) ||
	    to_vmx(vcpu)->exit_reason != EXIT_REASON_EPT_MISCONFIG) {
		rip = kvm_rip_read(vcpu);
		rip += vmcs_read32(VM_EXIT_INSTRUCTION_LEN);
		kvm_rip_write(vcpu, rip);
	} else {
		if (!kvm_emulate_instruction(vcpu, EMULTYPE_SKIP))
			return 0;
	}

	/* skipping an emulated instruction also counts */
	vmx_set_interrupt_shadow(vcpu, 0);

	return 1;
}