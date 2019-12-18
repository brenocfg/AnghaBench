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
struct thr_exit_args {scalar_t__ state; } ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 int kern_thr_exit (struct thread*) ; 
 int /*<<< orphan*/  kern_umtx_wake (struct thread*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  suword_lwpid (scalar_t__,int) ; 
 int /*<<< orphan*/  umtx_thread_exit (struct thread*) ; 

int
sys_thr_exit(struct thread *td, struct thr_exit_args *uap)
    /* long *state */
{

	umtx_thread_exit(td);

	/* Signal userland that it can free the stack. */
	if ((void *)uap->state != NULL) {
		suword_lwpid(uap->state, 1);
		kern_umtx_wake(td, uap->state, INT_MAX, 0);
	}

	return (kern_thr_exit(td));
}