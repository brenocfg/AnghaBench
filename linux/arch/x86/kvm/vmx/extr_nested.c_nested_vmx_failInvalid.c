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
 int X86_EFLAGS_AF ; 
 int X86_EFLAGS_CF ; 
 int X86_EFLAGS_OF ; 
 int X86_EFLAGS_PF ; 
 int X86_EFLAGS_SF ; 
 int X86_EFLAGS_ZF ; 
 int kvm_skip_emulated_instruction (struct kvm_vcpu*) ; 
 int vmx_get_rflags (struct kvm_vcpu*) ; 
 int /*<<< orphan*/  vmx_set_rflags (struct kvm_vcpu*,int) ; 

__attribute__((used)) static int nested_vmx_failInvalid(struct kvm_vcpu *vcpu)
{
	vmx_set_rflags(vcpu, (vmx_get_rflags(vcpu)
			& ~(X86_EFLAGS_PF | X86_EFLAGS_AF | X86_EFLAGS_ZF |
			    X86_EFLAGS_SF | X86_EFLAGS_OF))
			| X86_EFLAGS_CF);
	return kvm_skip_emulated_instruction(vcpu);
}