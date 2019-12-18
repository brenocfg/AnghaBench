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
struct vm {int maxcpus; int /*<<< orphan*/  suspended_cpus; int /*<<< orphan*/ * rendezvous_func; int /*<<< orphan*/  active_cpus; struct vcpu* vcpu; } ;
struct vcpu {int /*<<< orphan*/  mtx; } ;

/* Variables and functions */
 scalar_t__ CPU_CMP (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_SET_ATOMIC (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VCPU_CTR0 (struct vm*,int,char*) ; 
 int /*<<< orphan*/  VCPU_FROZEN ; 
 int /*<<< orphan*/  VCPU_SLEEPING ; 
 int /*<<< orphan*/  hz ; 
 int /*<<< orphan*/  msleep_spin (struct vcpu*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int /*<<< orphan*/  vcpu_notify_event (struct vm*,int,int) ; 
 int /*<<< orphan*/  vcpu_require_state_locked (struct vm*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 
 int /*<<< orphan*/  vm_handle_rendezvous (struct vm*,int) ; 

__attribute__((used)) static int
vm_handle_suspend(struct vm *vm, int vcpuid, bool *retu)
{
	int i, done;
	struct vcpu *vcpu;

	done = 0;
	vcpu = &vm->vcpu[vcpuid];

	CPU_SET_ATOMIC(vcpuid, &vm->suspended_cpus);

	/*
	 * Wait until all 'active_cpus' have suspended themselves.
	 *
	 * Since a VM may be suspended at any time including when one or
	 * more vcpus are doing a rendezvous we need to call the rendezvous
	 * handler while we are waiting to prevent a deadlock.
	 */
	vcpu_lock(vcpu);
	while (1) {
		if (CPU_CMP(&vm->suspended_cpus, &vm->active_cpus) == 0) {
			VCPU_CTR0(vm, vcpuid, "All vcpus suspended");
			break;
		}

		if (vm->rendezvous_func == NULL) {
			VCPU_CTR0(vm, vcpuid, "Sleeping during suspend");
			vcpu_require_state_locked(vm, vcpuid, VCPU_SLEEPING);
			msleep_spin(vcpu, &vcpu->mtx, "vmsusp", hz);
			vcpu_require_state_locked(vm, vcpuid, VCPU_FROZEN);
		} else {
			VCPU_CTR0(vm, vcpuid, "Rendezvous during suspend");
			vcpu_unlock(vcpu);
			vm_handle_rendezvous(vm, vcpuid);
			vcpu_lock(vcpu);
		}
	}
	vcpu_unlock(vcpu);

	/*
	 * Wakeup the other sleeping vcpus and return to userspace.
	 */
	for (i = 0; i < vm->maxcpus; i++) {
		if (CPU_ISSET(i, &vm->suspended_cpus)) {
			vcpu_notify_event(vm, i, false);
		}
	}

	*retu = true;
	return (0);
}