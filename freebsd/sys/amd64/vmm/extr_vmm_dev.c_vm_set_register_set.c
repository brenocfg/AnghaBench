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
typedef  int /*<<< orphan*/  uint64_t ;
struct vm {int dummy; } ;

/* Variables and functions */
 int vm_set_register (struct vm*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
vm_set_register_set(struct vm *vm, int vcpu, unsigned int count, int *regnum,
    uint64_t *regval)
{
	int error, i;

	error = 0;
	for (i = 0; i < count; i++) {
		error = vm_set_register(vm, vcpu, regnum[i], regval[i]);
		if (error)
			break;
	}
	return (error);
}