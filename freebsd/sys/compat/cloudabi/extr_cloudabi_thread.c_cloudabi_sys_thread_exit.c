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
struct cloudabi_sys_thread_exit_args {int /*<<< orphan*/  scope; int /*<<< orphan*/  lock; } ;
struct cloudabi_sys_lock_unlock_args {int /*<<< orphan*/  scope; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  cloudabi_sys_lock_unlock (struct thread*,struct cloudabi_sys_lock_unlock_args*) ; 
 int /*<<< orphan*/  exit1 (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_thr_exit (struct thread*) ; 
 int /*<<< orphan*/  umtx_thread_exit (struct thread*) ; 

int
cloudabi_sys_thread_exit(struct thread *td,
    struct cloudabi_sys_thread_exit_args *uap)
{
	struct cloudabi_sys_lock_unlock_args cloudabi_sys_lock_unlock_args = {
		.lock = uap->lock,
		.scope = uap->scope,
	};

	umtx_thread_exit(td);

        /* Wake up joining thread. */
	cloudabi_sys_lock_unlock(td, &cloudabi_sys_lock_unlock_args);

        /*
	 * Attempt to terminate the thread. Terminate the process if
	 * it's the last thread.
	 */
	kern_thr_exit(td);
	exit1(td, 0, 0);
	/* NOTREACHED */
}