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
struct thread_create_args {int /*<<< orphan*/  tcb; int /*<<< orphan*/  attr; int /*<<< orphan*/  tid; } ;
struct thread {int /*<<< orphan*/  td_tid; } ;

/* Variables and functions */
 int cloudabi64_thread_setregs (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
initialize_thread(struct thread *td, void *thunk)
{
	struct thread_create_args *args = thunk;

	/* Save the thread ID, so it can be returned. */
	args->tid = td->td_tid;

	/* Set up initial register contents. */
	return (cloudabi64_thread_setregs(td, &args->attr, args->tcb));
}