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
struct vm {int maxcpus; int /*<<< orphan*/  debug_cpus; int /*<<< orphan*/  active_cpus; } ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (int,int /*<<< orphan*/ *) ; 
 int EINVAL ; 
 int /*<<< orphan*/  vcpu_notify_event (struct vm*,int,int) ; 

int
vm_suspend_cpu(struct vm *vm, int vcpuid)
{
	int i;

	if (vcpuid < -1 || vcpuid >= vm->maxcpus)
		return (EINVAL);

	if (vcpuid == -1) {
		vm->debug_cpus = vm->active_cpus;
		for (i = 0; i < vm->maxcpus; i++) {
			if (CPU_ISSET(i, &vm->active_cpus))
				vcpu_notify_event(vm, i, false);
		}
	} else {
		if (!CPU_ISSET(vcpuid, &vm->active_cpus))
			return (EINVAL);

		CPU_SET_ATOMIC(vcpuid, &vm->debug_cpus);
		vcpu_notify_event(vm, vcpuid, false);
	}
	return (0);
}