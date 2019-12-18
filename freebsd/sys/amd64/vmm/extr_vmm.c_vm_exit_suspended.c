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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_3__ {scalar_t__ how; } ;
struct TYPE_4__ {TYPE_1__ suspended; } ;
struct vm_exit {TYPE_2__ u; int /*<<< orphan*/  exitcode; scalar_t__ inst_length; int /*<<< orphan*/  rip; } ;
struct vm {scalar_t__ suspend; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  VM_EXITCODE_SUSPENDED ; 
 scalar_t__ VM_SUSPEND_LAST ; 
 scalar_t__ VM_SUSPEND_NONE ; 
 struct vm_exit* vm_exitinfo (struct vm*,int) ; 

void
vm_exit_suspended(struct vm *vm, int vcpuid, uint64_t rip)
{
	struct vm_exit *vmexit;

	KASSERT(vm->suspend > VM_SUSPEND_NONE && vm->suspend < VM_SUSPEND_LAST,
	    ("vm_exit_suspended: invalid suspend type %d", vm->suspend));

	vmexit = vm_exitinfo(vm, vcpuid);
	vmexit->rip = rip;
	vmexit->inst_length = 0;
	vmexit->exitcode = VM_EXITCODE_SUSPENDED;
	vmexit->u.suspended.how = vm->suspend;
}