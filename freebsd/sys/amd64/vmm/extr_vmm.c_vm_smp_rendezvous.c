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
typedef  int /*<<< orphan*/ * vm_rendezvous_func_t ;
struct vm {int maxcpus; int /*<<< orphan*/  rendezvous_mtx; int /*<<< orphan*/ * rendezvous_func; void* rendezvous_arg; int /*<<< orphan*/  rendezvous_done_cpus; int /*<<< orphan*/  rendezvous_req_cpus; } ;
typedef  int /*<<< orphan*/  cpuset_t ;

/* Variables and functions */
 scalar_t__ CPU_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CPU_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  RENDEZVOUS_CTR0 (struct vm*,int,char*) ; 
 int /*<<< orphan*/  WARN_PANIC ; 
 int /*<<< orphan*/  WITNESS_WARN (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mtx_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vcpu_notify_event (struct vm*,int,int) ; 
 int /*<<< orphan*/  vm_handle_rendezvous (struct vm*,int) ; 

void
vm_smp_rendezvous(struct vm *vm, int vcpuid, cpuset_t dest,
    vm_rendezvous_func_t func, void *arg)
{
	int i;

	/*
	 * Enforce that this function is called without any locks
	 */
	WITNESS_WARN(WARN_PANIC, NULL, "vm_smp_rendezvous");
	KASSERT(vcpuid == -1 || (vcpuid >= 0 && vcpuid < vm->maxcpus),
	    ("vm_smp_rendezvous: invalid vcpuid %d", vcpuid));

restart:
	mtx_lock(&vm->rendezvous_mtx);
	if (vm->rendezvous_func != NULL) {
		/*
		 * If a rendezvous is already in progress then we need to
		 * call the rendezvous handler in case this 'vcpuid' is one
		 * of the targets of the rendezvous.
		 */
		RENDEZVOUS_CTR0(vm, vcpuid, "Rendezvous already in progress");
		mtx_unlock(&vm->rendezvous_mtx);
		vm_handle_rendezvous(vm, vcpuid);
		goto restart;
	}
	KASSERT(vm->rendezvous_func == NULL, ("vm_smp_rendezvous: previous "
	    "rendezvous is still in progress"));

	RENDEZVOUS_CTR0(vm, vcpuid, "Initiating rendezvous");
	vm->rendezvous_req_cpus = dest;
	CPU_ZERO(&vm->rendezvous_done_cpus);
	vm->rendezvous_arg = arg;
	vm->rendezvous_func = func;
	mtx_unlock(&vm->rendezvous_mtx);

	/*
	 * Wake up any sleeping vcpus and trigger a VM-exit in any running
	 * vcpus so they handle the rendezvous as soon as possible.
	 */
	for (i = 0; i < vm->maxcpus; i++) {
		if (CPU_ISSET(i, &dest))
			vcpu_notify_event(vm, i, false);
	}

	vm_handle_rendezvous(vm, vcpuid);
}