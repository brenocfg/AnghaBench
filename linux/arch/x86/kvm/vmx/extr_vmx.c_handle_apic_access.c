#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 unsigned long APIC_ACCESS_OFFSET ; 
 unsigned long APIC_ACCESS_TYPE ; 
 int APIC_EOI ; 
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 int TYPE_LINEAR_APIC_INST_WRITE ; 
 int /*<<< orphan*/  fasteoi ; 
 int kvm_emulate_instruction (struct kvm_vcpu*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_lapic_set_eoi (struct kvm_vcpu*) ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int handle_apic_access(struct kvm_vcpu *vcpu)
{
	if (likely(fasteoi)) {
		unsigned long exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
		int access_type, offset;

		access_type = exit_qualification & APIC_ACCESS_TYPE;
		offset = exit_qualification & APIC_ACCESS_OFFSET;
		/*
		 * Sane guest uses MOV to write EOI, with written value
		 * not cared. So make a short-circuit here by avoiding
		 * heavy instruction emulation.
		 */
		if ((access_type == TYPE_LINEAR_APIC_INST_WRITE) &&
		    (offset == APIC_EOI)) {
			kvm_lapic_set_eoi(vcpu);
			return kvm_skip_emulated_instruction(vcpu);
		}
	}
	return kvm_emulate_instruction(vcpu, 0);
}