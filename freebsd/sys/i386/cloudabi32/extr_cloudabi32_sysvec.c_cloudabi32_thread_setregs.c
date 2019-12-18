#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct thread {TYPE_1__* td_frame; int /*<<< orphan*/  td_tid; } ;
struct TYPE_7__ {scalar_t__ ss_size; int /*<<< orphan*/  ss_sp; } ;
typedef  TYPE_2__ stack_t ;
struct TYPE_8__ {int /*<<< orphan*/  argument; int /*<<< orphan*/  entry_point; scalar_t__ stack_len; int /*<<< orphan*/  stack; } ;
typedef  TYPE_3__ cloudabi32_threadattr_t ;
typedef  int /*<<< orphan*/  args ;
struct TYPE_6__ {scalar_t__ tf_esp; } ;

/* Variables and functions */
 int /*<<< orphan*/  TO_PTR (int /*<<< orphan*/ ) ; 
 int copyout (int /*<<< orphan*/ *,void*,int) ; 
 int /*<<< orphan*/  cpu_set_upcall (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int cpu_set_user_tls (struct thread*,void*) ; 

int
cloudabi32_thread_setregs(struct thread *td,
    const cloudabi32_threadattr_t *attr, uint32_t tcb)
{
	stack_t stack;
	uint32_t args[3];
	void *frameptr;
	int error;

	/* Perform standard register initialization. */
	stack.ss_sp = TO_PTR(attr->stack);
	stack.ss_size = attr->stack_len - sizeof(args);
	cpu_set_upcall(td, TO_PTR(attr->entry_point), NULL, &stack);

	/*
	 * Copy the arguments for the thread entry point onto the stack
	 * (args[1] and args[2]). Similar to process startup, use the
	 * otherwise unused return address (args[0]) for TLS.
	 */
	args[0] = tcb;
	args[1] = td->td_tid;
	args[2] = attr->argument;
	frameptr = (void *)td->td_frame->tf_esp;
	error = copyout(args, frameptr, sizeof(args));
	if (error != 0)
		return (error);

	return (cpu_set_user_tls(td, frameptr));
}