#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {int /*<<< orphan*/  td_tid; } ;
struct thr_param {int /*<<< orphan*/  tls_base; int /*<<< orphan*/  arg; int /*<<< orphan*/  start_func; int /*<<< orphan*/  stack_size; int /*<<< orphan*/  stack_base; int /*<<< orphan*/ * parent_tid; int /*<<< orphan*/ * child_tid; } ;
struct TYPE_3__ {int /*<<< orphan*/  ss_size; int /*<<< orphan*/  ss_sp; } ;
typedef  TYPE_1__ stack_t ;

/* Variables and functions */
 int EFAULT ; 
 int /*<<< orphan*/  cpu_set_upcall (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int cpu_set_user_tls (struct thread*,int /*<<< orphan*/ ) ; 
 scalar_t__ suword_lwpid (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
thr_new_initthr(struct thread *td, void *thunk)
{
	stack_t stack;
	struct thr_param *param;

	/*
	 * Here we copy out tid to two places, one for child and one
	 * for parent, because pthread can create a detached thread,
	 * if parent wants to safely access child tid, it has to provide
	 * its storage, because child thread may exit quickly and
	 * memory is freed before parent thread can access it.
	 */
	param = thunk;
	if ((param->child_tid != NULL &&
	    suword_lwpid(param->child_tid, td->td_tid)) ||
	    (param->parent_tid != NULL &&
	    suword_lwpid(param->parent_tid, td->td_tid)))
		return (EFAULT);

	/* Set up our machine context. */
	stack.ss_sp = param->stack_base;
	stack.ss_size = param->stack_size;
	/* Set upcall address to user thread entry function. */
	cpu_set_upcall(td, param->start_func, param->arg, &stack);
	/* Setup user TLS address and TLS pointer register. */
	return (cpu_set_user_tls(td, param->tls_base));
}