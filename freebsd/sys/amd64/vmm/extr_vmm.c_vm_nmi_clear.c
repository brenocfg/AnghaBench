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
struct vcpu {scalar_t__ nmi_pending; } ;

/* Variables and functions */
 int /*<<< orphan*/  VCPU_NMI_COUNT ; 
 int /*<<< orphan*/  panic (char*,...) ; 
 int /*<<< orphan*/  vmm_stat_incr (struct vm*,int,int /*<<< orphan*/ ,int) ; 

void
vm_nmi_clear(struct vm *vm, int vcpuid)
{
	struct vcpu *vcpu;

	if (vcpuid < 0 || vcpuid >= vm->maxcpus)
		panic("vm_nmi_pending: invalid vcpuid %d", vcpuid);

	vcpu = &vm->vcpu[vcpuid];

	if (vcpu->nmi_pending == 0)
		panic("vm_nmi_clear: inconsistent nmi_pending state");

	vcpu->nmi_pending = 0;
	vmm_stat_incr(vm, vcpuid, VCPU_NMI_COUNT, 1);
}