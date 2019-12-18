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
struct thread {int dummy; } ;
struct linux_sys_futex_args {int* uaddr; int val; scalar_t__ val3; int /*<<< orphan*/ * uaddr2; int /*<<< orphan*/ * timeout; int /*<<< orphan*/  op; } ;
struct linux_emuldata {int* child_clear_tid; int /*<<< orphan*/  em_tid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  LINUX_CTR1 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LINUX_CTR2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  LINUX_FUTEX_WAKE ; 
 struct linux_emuldata* em_find (struct thread*) ; 
 int /*<<< orphan*/  linux_msg (struct thread*,char*) ; 
 int linux_sys_futex (struct thread*,struct linux_sys_futex_args*) ; 
 int /*<<< orphan*/  release_futexes (struct thread*,struct linux_emuldata*) ; 
 int suword32 (int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  thread_detach ; 

void
linux_thread_detach(struct thread *td)
{
	struct linux_sys_futex_args cup;
	struct linux_emuldata *em;
	int *child_clear_tid;
	int error;

	em = em_find(td);
	KASSERT(em != NULL, ("thread_detach: emuldata not found.\n"));

	LINUX_CTR1(thread_detach, "thread(%d)", em->em_tid);

	release_futexes(td, em);

	child_clear_tid = em->child_clear_tid;

	if (child_clear_tid != NULL) {

		LINUX_CTR2(thread_detach, "thread(%d) %p",
		    em->em_tid, child_clear_tid);

		error = suword32(child_clear_tid, 0);
		if (error != 0)
			return;

		cup.uaddr = child_clear_tid;
		cup.op = LINUX_FUTEX_WAKE;
		cup.val = 1;		/* wake one */
		cup.timeout = NULL;
		cup.uaddr2 = NULL;
		cup.val3 = 0;
		error = linux_sys_futex(td, &cup);
		/*
		 * this cannot happen at the moment and if this happens it
		 * probably means there is a user space bug
		 */
		if (error != 0)
			linux_msg(td, "futex stuff in thread_detach failed.");
	}
}