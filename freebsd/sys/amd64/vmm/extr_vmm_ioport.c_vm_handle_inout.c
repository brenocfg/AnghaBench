#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bytes; int /*<<< orphan*/  port; scalar_t__ rep; scalar_t__ string; } ;
struct TYPE_4__ {TYPE_1__ inout; } ;
struct vm_exit {TYPE_2__ u; } ;
struct vm {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VCPU_CTR4 (struct vm*,int,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int emulate_inout_port (struct vm*,int,struct vm_exit*,int*) ; 
 int emulate_inout_str (struct vm*,int,struct vm_exit*,int*) ; 
 int /*<<< orphan*/  inout_instruction (struct vm_exit*) ; 

int
vm_handle_inout(struct vm *vm, int vcpuid, struct vm_exit *vmexit, bool *retu)
{
	int bytes, error;

	bytes = vmexit->u.inout.bytes;
	KASSERT(bytes == 1 || bytes == 2 || bytes == 4,
	    ("vm_handle_inout: invalid operand size %d", bytes));

	if (vmexit->u.inout.string)
		error = emulate_inout_str(vm, vcpuid, vmexit, retu);
	else
		error = emulate_inout_port(vm, vcpuid, vmexit, retu);

	VCPU_CTR4(vm, vcpuid, "%s%s 0x%04x: %s",
	    vmexit->u.inout.rep ? "rep " : "",
	    inout_instruction(vmexit),
	    vmexit->u.inout.port,
	    error ? "error" : (*retu ? "userspace" : "handled"));

	return (error);
}