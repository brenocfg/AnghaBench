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
struct vm {int maxcpus; int /*<<< orphan*/  cookie; } ;

/* Variables and functions */
 int EINVAL ; 
 int VMSETCAP (int /*<<< orphan*/ ,int,int,int) ; 
 int VM_CAP_MAX ; 

int
vm_set_capability(struct vm *vm, int vcpu, int type, int val)
{
	if (vcpu < 0 || vcpu >= vm->maxcpus)
		return (EINVAL);

	if (type < 0 || type >= VM_CAP_MAX)
		return (EINVAL);

	return (VMSETCAP(vm->cookie, vcpu, type, val));
}