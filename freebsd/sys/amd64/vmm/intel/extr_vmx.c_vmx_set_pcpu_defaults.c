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
struct vmxstate {scalar_t__ lastcpu; } ;
struct vmx {int /*<<< orphan*/  vm; struct vmxstate* state; } ;
typedef  int /*<<< orphan*/  pmap_t ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_MIGRATIONS ; 
 int /*<<< orphan*/  VMCS_HOST_GDTR_BASE ; 
 int /*<<< orphan*/  VMCS_HOST_GS_BASE ; 
 int /*<<< orphan*/  VMCS_HOST_TR_BASE ; 
 scalar_t__ curcpu ; 
 int /*<<< orphan*/  vmcs_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmm_get_host_gdtrbase () ; 
 int /*<<< orphan*/  vmm_get_host_gsbase () ; 
 int /*<<< orphan*/  vmm_get_host_trbase () ; 
 int /*<<< orphan*/  vmm_stat_incr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vmx_invvpid (struct vmx*,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
vmx_set_pcpu_defaults(struct vmx *vmx, int vcpu, pmap_t pmap)
{
	struct vmxstate *vmxstate;

	vmxstate = &vmx->state[vcpu];
	if (vmxstate->lastcpu == curcpu)
		return;

	vmxstate->lastcpu = curcpu;

	vmm_stat_incr(vmx->vm, vcpu, VCPU_MIGRATIONS, 1);

	vmcs_write(VMCS_HOST_TR_BASE, vmm_get_host_trbase());
	vmcs_write(VMCS_HOST_GDTR_BASE, vmm_get_host_gdtrbase());
	vmcs_write(VMCS_HOST_GS_BASE, vmm_get_host_gsbase());
	vmx_invvpid(vmx, vcpu, pmap, 1);
}