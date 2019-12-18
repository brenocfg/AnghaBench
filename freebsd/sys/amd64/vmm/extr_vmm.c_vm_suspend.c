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
struct vm {int maxcpus; int /*<<< orphan*/  active_cpus; int /*<<< orphan*/  suspend; } ;
typedef  enum vm_suspend_how { ____Placeholder_vm_suspend_how } vm_suspend_how ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int EALREADY ; 
 int EINVAL ; 
 int /*<<< orphan*/  VM_CTR1 (struct vm*,char*,int) ; 
 int /*<<< orphan*/  VM_CTR2 (struct vm*,char*,int /*<<< orphan*/ ,int) ; 
 int VM_SUSPEND_LAST ; 
 int VM_SUSPEND_NONE ; 
 scalar_t__ atomic_cmpset_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vcpu_notify_event (struct vm*,int,int) ; 

int
vm_suspend(struct vm *vm, enum vm_suspend_how how)
{
	int i;

	if (how <= VM_SUSPEND_NONE || how >= VM_SUSPEND_LAST)
		return (EINVAL);

	if (atomic_cmpset_int(&vm->suspend, 0, how) == 0) {
		VM_CTR2(vm, "virtual machine already suspended %d/%d",
		    vm->suspend, how);
		return (EALREADY);
	}

	VM_CTR1(vm, "virtual machine successfully suspended %d", how);

	/*
	 * Notify all active vcpus that they are now suspended.
	 */
	for (i = 0; i < vm->maxcpus; i++) {
		if (CPU_ISSET(i, &vm->active_cpus))
			vcpu_notify_event(vm, i, false);
	}

	return (0);
}