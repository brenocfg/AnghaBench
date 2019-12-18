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
struct vcpu {int nmi_pending; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  vcpu_notify_event (struct vm*,int,int) ; 

int
vm_inject_nmi(struct vm *vm, int vcpuid)
{
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= vm->maxcpus)
		return (EINVAL);

	vcpu = &vm->vcpu[vcpuid];

	vcpu->nmi_pending = 1;
	vcpu_notify_event(vm, vcpuid, false);
	return (0);
}