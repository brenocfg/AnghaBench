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
typedef  int uint32_t ;
struct vmx {int /*<<< orphan*/  vm; } ;
struct TYPE_3__ {scalar_t__ exit_reason; } ;
struct TYPE_4__ {TYPE_1__ vmx; } ;
struct vm_exit {TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ EXIT_REASON_EXCEPTION ; 
 int IDT_NMI ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int PSL_I ; 
 int /*<<< orphan*/  VCPU_CTR0 (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  VMCS_EXIT_INTR_INFO ; 
 int VMCS_INTR_T_MASK ; 
 int VMCS_INTR_T_NMI ; 
 int VMCS_INTR_VALID ; 
 int read_rflags () ; 
 int vmcs_read (int /*<<< orphan*/ ) ; 

__attribute__((used)) static __inline void
vmx_exit_handle_nmi(struct vmx *vmx, int vcpuid, struct vm_exit *vmexit)
{
	uint32_t intr_info;

	KASSERT((read_rflags() & PSL_I) == 0, ("interrupts enabled"));

	if (vmexit->u.vmx.exit_reason != EXIT_REASON_EXCEPTION)
		return;

	intr_info = vmcs_read(VMCS_EXIT_INTR_INFO);
	KASSERT((intr_info & VMCS_INTR_VALID) != 0,
	    ("VM exit interruption info invalid: %#x", intr_info));

	if ((intr_info & VMCS_INTR_T_MASK) == VMCS_INTR_T_NMI) {
		KASSERT((intr_info & 0xff) == IDT_NMI, ("VM exit due "
		    "to NMI has invalid vector: %#x", intr_info));
		VCPU_CTR0(vmx->vm, vcpuid, "Vectoring to NMI handler");
		__asm __volatile("int $2");
	}
}