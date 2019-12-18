#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  host_apf_reason; } ;
struct TYPE_6__ {TYPE_1__ apf; } ;
struct TYPE_7__ {TYPE_2__ arch; } ;
struct vcpu_vmx {TYPE_3__ vcpu; int /*<<< orphan*/  exit_intr_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  VM_EXIT_INTR_INFO ; 
 scalar_t__ is_machine_check (int /*<<< orphan*/ ) ; 
 scalar_t__ is_nmi (int /*<<< orphan*/ ) ; 
 scalar_t__ is_page_fault (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kvm_after_interrupt (TYPE_3__*) ; 
 int /*<<< orphan*/  kvm_before_interrupt (TYPE_3__*) ; 
 int /*<<< orphan*/  kvm_machine_check () ; 
 int /*<<< orphan*/  kvm_read_and_reset_pf_reason () ; 
 int /*<<< orphan*/  vmcs_read32 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_exception_nmi_irqoff(struct vcpu_vmx *vmx)
{
	vmx->exit_intr_info = vmcs_read32(VM_EXIT_INTR_INFO);

	/* if exit due to PF check for async PF */
	if (is_page_fault(vmx->exit_intr_info))
		vmx->vcpu.arch.apf.host_apf_reason = kvm_read_and_reset_pf_reason();

	/* Handle machine checks before interrupts are enabled */
	if (is_machine_check(vmx->exit_intr_info))
		kvm_machine_check();

	/* We need to handle NMIs before interrupts are enabled */
	if (is_nmi(vmx->exit_intr_info)) {
		kvm_before_interrupt(&vmx->vcpu);
		asm("int $2");
		kvm_after_interrupt(&vmx->vcpu);
	}
}