#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct vmspace {scalar_t__ vm_daddr; int /*<<< orphan*/  vm_dsize; } ;
struct thread {void** td_retval; TYPE_1__* td_proc; } ;
struct linux_brk_args {scalar_t__ dsend; } ;
typedef  void* register_t ;
typedef  scalar_t__ caddr_t ;
struct TYPE_2__ {struct vmspace* p_vmspace; } ;

/* Variables and functions */
 uintptr_t ctob (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_break (struct thread*,uintptr_t*) ; 

int
linux_brk(struct thread *td, struct linux_brk_args *args)
{
	struct vmspace *vm = td->td_proc->p_vmspace;
	uintptr_t new, old;

	old = (uintptr_t)vm->vm_daddr + ctob(vm->vm_dsize);
	new = (uintptr_t)args->dsend;
	if ((caddr_t)new > vm->vm_daddr && !kern_break(td, &new))
		td->td_retval[0] = (register_t)new;
	else
		td->td_retval[0] = (register_t)old;

	return (0);
}