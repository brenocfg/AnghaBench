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
typedef  int /*<<< orphan*/  uint64_t ;
struct vmx {int /*<<< orphan*/ * vmcs; int /*<<< orphan*/ * ctx; int /*<<< orphan*/  vm; } ;

/* Variables and functions */
 int VM_REG_GUEST_INTR_SHADOW ; 
 int curcpu ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 
 int vcpu_is_running (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vm_name (int /*<<< orphan*/ ) ; 
 int vmcs_getreg (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ *) ; 
 int vmx_get_intr_shadow (struct vmx*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ vmxctx_getreg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
vmx_getreg(void *arg, int vcpu, int reg, uint64_t *retval)
{
	int running, hostcpu;
	struct vmx *vmx = arg;

	running = vcpu_is_running(vmx->vm, vcpu, &hostcpu);
	if (running && hostcpu != curcpu)
		panic("vmx_getreg: %s%d is running", vm_name(vmx->vm), vcpu);

	if (reg == VM_REG_GUEST_INTR_SHADOW)
		return (vmx_get_intr_shadow(vmx, vcpu, running, retval));

	if (vmxctx_getreg(&vmx->ctx[vcpu], reg, retval) == 0)
		return (0);

	return (vmcs_getreg(&vmx->vmcs[vcpu], running, reg, retval));
}