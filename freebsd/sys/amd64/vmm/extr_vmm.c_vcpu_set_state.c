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
struct vm {int maxcpus; struct vcpu* vcpu; } ;
struct vcpu {int dummy; } ;
typedef  enum vcpu_state { ____Placeholder_vcpu_state } vcpu_state ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int) ; 
 int /*<<< orphan*/  vcpu_lock (struct vcpu*) ; 
 int vcpu_set_state_locked (struct vm*,int,int,int) ; 
 int /*<<< orphan*/  vcpu_unlock (struct vcpu*) ; 

int
vcpu_set_state(struct vm *vm, int vcpuid, enum vcpu_state newstate,
    bool from_idle)
{
	int error;
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= vm->maxcpus)
		panic("vm_set_run_state: invalid vcpuid %d", vcpuid);

	vcpu = &vm->vcpu[vcpuid];

	vcpu_lock(vcpu);
	error = vcpu_set_state_locked(vm, vcpuid, newstate, from_idle);
	vcpu_unlock(vcpu);

	return (error);
}