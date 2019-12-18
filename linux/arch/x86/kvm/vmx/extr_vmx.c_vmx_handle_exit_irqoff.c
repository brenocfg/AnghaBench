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
struct vcpu_vmx {scalar_t__ exit_reason; } ;
struct kvm_vcpu {int dummy; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_EXCEPTION_NMI ; 
 scalar_t__ EXIT_REASON_EXTERNAL_INTERRUPT ; 
 int /*<<< orphan*/  handle_exception_nmi_irqoff (struct vcpu_vmx*) ; 
 int /*<<< orphan*/  handle_external_interrupt_irqoff (struct kvm_vcpu*) ; 
 struct vcpu_vmx* to_vmx (struct kvm_vcpu*) ; 

__attribute__((used)) static void vmx_handle_exit_irqoff(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);

	if (vmx->exit_reason == EXIT_REASON_EXTERNAL_INTERRUPT)
		handle_external_interrupt_irqoff(vcpu);
	else if (vmx->exit_reason == EXIT_REASON_EXCEPTION_NMI)
		handle_exception_nmi_irqoff(vmx);
}