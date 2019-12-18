#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u64 ;
struct vmcs12 {int vm_entry_controls; int guest_ia32_efer; } ;
struct TYPE_5__ {int efer; } ;
struct TYPE_6__ {TYPE_2__ arch; } ;
struct TYPE_4__ {scalar_t__ nested_run_pending; } ;
struct vcpu_vmx {TYPE_3__ vcpu; TYPE_1__ nested; } ;

/* Variables and functions */
 int EFER_LMA ; 
 int EFER_LME ; 
 int VM_ENTRY_IA32E_MODE ; 
 int VM_ENTRY_LOAD_IA32_EFER ; 

__attribute__((used)) static u64 nested_vmx_calc_efer(struct vcpu_vmx *vmx, struct vmcs12 *vmcs12)
{
	if (vmx->nested.nested_run_pending &&
	    (vmcs12->vm_entry_controls & VM_ENTRY_LOAD_IA32_EFER))
		return vmcs12->guest_ia32_efer;
	else if (vmcs12->vm_entry_controls & VM_ENTRY_IA32E_MODE)
		return vmx->vcpu.arch.efer | (EFER_LMA | EFER_LME);
	else
		return vmx->vcpu.arch.efer & ~(EFER_LMA | EFER_LME);
}