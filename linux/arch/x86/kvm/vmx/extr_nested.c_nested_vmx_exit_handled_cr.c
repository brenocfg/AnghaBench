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
struct vmcs12 {unsigned long cr0_guest_host_mask; unsigned long cr0_read_shadow; int cr3_target_count; unsigned long cr3_target_value0; unsigned long cr3_target_value1; unsigned long cr3_target_value2; unsigned long cr3_target_value3; unsigned long cr4_guest_host_mask; unsigned long cr4_read_shadow; int cpu_based_vm_exec_control; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_BASED_CR3_LOAD_EXITING ; 
 int CPU_BASED_CR3_STORE_EXITING ; 
 int /*<<< orphan*/  CPU_BASED_CR8_LOAD_EXITING ; 
 int CPU_BASED_CR8_STORE_EXITING ; 
 int /*<<< orphan*/  EXIT_QUALIFICATION ; 
 unsigned long LMSW_SOURCE_DATA_SHIFT ; 
 int X86_CR0_TS ; 
 unsigned long kvm_register_readl (struct kvm_vcpu*,int) ; 
 int /*<<< orphan*/  nested_cpu_has (struct vmcs12*,int /*<<< orphan*/ ) ; 
 unsigned long vmcs_readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool nested_vmx_exit_handled_cr(struct kvm_vcpu *vcpu,
	struct vmcs12 *vmcs12)
{
	unsigned long exit_qualification = vmcs_readl(EXIT_QUALIFICATION);
	int cr = exit_qualification & 15;
	int reg;
	unsigned long val;

	switch ((exit_qualification >> 4) & 3) {
	case 0: /* mov to cr */
		reg = (exit_qualification >> 8) & 15;
		val = kvm_register_readl(vcpu, reg);
		switch (cr) {
		case 0:
			if (vmcs12->cr0_guest_host_mask &
			    (val ^ vmcs12->cr0_read_shadow))
				return true;
			break;
		case 3:
			if ((vmcs12->cr3_target_count >= 1 &&
					vmcs12->cr3_target_value0 == val) ||
				(vmcs12->cr3_target_count >= 2 &&
					vmcs12->cr3_target_value1 == val) ||
				(vmcs12->cr3_target_count >= 3 &&
					vmcs12->cr3_target_value2 == val) ||
				(vmcs12->cr3_target_count >= 4 &&
					vmcs12->cr3_target_value3 == val))
				return false;
			if (nested_cpu_has(vmcs12, CPU_BASED_CR3_LOAD_EXITING))
				return true;
			break;
		case 4:
			if (vmcs12->cr4_guest_host_mask &
			    (vmcs12->cr4_read_shadow ^ val))
				return true;
			break;
		case 8:
			if (nested_cpu_has(vmcs12, CPU_BASED_CR8_LOAD_EXITING))
				return true;
			break;
		}
		break;
	case 2: /* clts */
		if ((vmcs12->cr0_guest_host_mask & X86_CR0_TS) &&
		    (vmcs12->cr0_read_shadow & X86_CR0_TS))
			return true;
		break;
	case 1: /* mov from cr */
		switch (cr) {
		case 3:
			if (vmcs12->cpu_based_vm_exec_control &
			    CPU_BASED_CR3_STORE_EXITING)
				return true;
			break;
		case 8:
			if (vmcs12->cpu_based_vm_exec_control &
			    CPU_BASED_CR8_STORE_EXITING)
				return true;
			break;
		}
		break;
	case 3: /* lmsw */
		/*
		 * lmsw can change bits 1..3 of cr0, and only set bit 0 of
		 * cr0. Other attempted changes are ignored, with no exit.
		 */
		val = (exit_qualification >> LMSW_SOURCE_DATA_SHIFT) & 0x0f;
		if (vmcs12->cr0_guest_host_mask & 0xe &
		    (val ^ vmcs12->cr0_read_shadow))
			return true;
		if ((vmcs12->cr0_guest_host_mask & 0x1) &&
		    !(vmcs12->cr0_read_shadow & 0x1) &&
		    (val & 0x1))
			return true;
		break;
	}
	return false;
}