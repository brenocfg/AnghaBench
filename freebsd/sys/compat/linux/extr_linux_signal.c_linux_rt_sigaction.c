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
struct linux_rt_sigaction_args {int sigsetsize; int /*<<< orphan*/ * oact; int /*<<< orphan*/ * act; int /*<<< orphan*/  sig; } ;
typedef  int /*<<< orphan*/  l_sigset_t ;
typedef  int /*<<< orphan*/  l_sigaction_t ;

/* Variables and functions */
 int EINVAL ; 
 int copyin (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int linux_do_sigaction (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
linux_rt_sigaction(struct thread *td, struct linux_rt_sigaction_args *args)
{
	l_sigaction_t nsa, osa;
	int error;

	if (args->sigsetsize != sizeof(l_sigset_t))
		return (EINVAL);

	if (args->act != NULL) {
		error = copyin(args->act, &nsa, sizeof(l_sigaction_t));
		if (error)
			return (error);
	}

	error = linux_do_sigaction(td, args->sig,
				   args->act ? &nsa : NULL,
				   args->oact ? &osa : NULL);

	if (args->oact != NULL && !error) {
		error = copyout(&osa, args->oact, sizeof(l_sigaction_t));
	}

	return (error);
}