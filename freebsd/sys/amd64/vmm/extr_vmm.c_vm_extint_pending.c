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
struct vcpu {int extint_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int) ; 

int
vm_extint_pending(struct vm *vm, int vcpuid)
{
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= vm->maxcpus)
		panic("vm_extint_pending: invalid vcpuid %d", vcpuid);

	vcpu = &vm->vcpu[vcpuid];

	return (vcpu->extint_pending);
}