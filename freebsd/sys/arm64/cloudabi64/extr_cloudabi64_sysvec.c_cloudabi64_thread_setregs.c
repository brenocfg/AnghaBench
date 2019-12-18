#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct trapframe {int /*<<< orphan*/ * tf_x; } ;
struct thread {int /*<<< orphan*/  td_tid; struct trapframe* td_frame; } ;
struct TYPE_5__ {int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;
typedef  TYPE_1__ stack_t ;
struct TYPE_6__ {int /*<<< orphan*/  argument; int /*<<< orphan*/  entry_point; int /*<<< orphan*/  stack_len; int /*<<< orphan*/  stack; } ;
typedef  TYPE_2__ cloudabi64_threadattr_t ;

/* Variables and functions */
 int /*<<< orphan*/  TO_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_set_upcall (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int cpu_set_user_tls (struct thread*,int /*<<< orphan*/ ) ; 

int
cloudabi64_thread_setregs(struct thread *td,
    const cloudabi64_threadattr_t *attr, uint64_t tcb)
{
	struct trapframe *frame;
	stack_t stack;

	/* Perform standard register initialization. */
	stack.ss_sp = TO_PTR(attr->stack);
	stack.ss_size = attr->stack_len;
	cpu_set_upcall(td, TO_PTR(attr->entry_point), NULL, &stack);

	/*
	 * Pass in the thread ID of the new thread and the argument
	 * pointer provided by the parent thread in as arguments to the
	 * entry point.
	 */
	frame = td->td_frame;
	frame->tf_x[0] = td->td_tid;
	frame->tf_x[1] = attr->argument;

	/* Set up TLS. */
	return (cpu_set_user_tls(td, TO_PTR(tcb)));
}