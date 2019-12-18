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
struct vmx {int /*<<< orphan*/ * vmcs; int /*<<< orphan*/  vm; } ;
struct seg_desc {int dummy; } ;

/* Variables and functions */
 int curcpu ; 
 int /*<<< orphan*/  panic (char*,int /*<<< orphan*/ ,int) ; 
 int vcpu_is_running (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  vm_name (int /*<<< orphan*/ ) ; 
 int vmcs_getdesc (int /*<<< orphan*/ *,int,int,struct seg_desc*) ; 

__attribute__((used)) static int
vmx_getdesc(void *arg, int vcpu, int reg, struct seg_desc *desc)
{
	int hostcpu, running;
	struct vmx *vmx = arg;

	running = vcpu_is_running(vmx->vm, vcpu, &hostcpu);
	if (running && hostcpu != curcpu)
		panic("vmx_getdesc: %s%d is running", vm_name(vmx->vm), vcpu);

	return (vmcs_getdesc(&vmx->vmcs[vcpu], running, reg, desc));
}