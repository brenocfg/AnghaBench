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
struct vm_exit {int dummy; } ;
struct vm {int maxcpus; struct vcpu* vcpu; } ;
struct vcpu {struct vm_exit exitinfo; } ;

/* Variables and functions */
 int /*<<< orphan*/  panic (char*,int) ; 

struct vm_exit *
vm_exitinfo(struct vm *vm, int cpuid)
{
	struct vcpu *vcpu;

	if (cpuid < 0 || cpuid >= vm->maxcpus)
		panic("vm_exitinfo: invalid cpuid %d", cpuid);

	vcpu = &vm->vcpu[cpuid];

	return (&vcpu->exitinfo);
}