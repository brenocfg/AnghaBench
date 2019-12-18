#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {int* td_retval; TYPE_1__* td_proc; } ;
struct sigwait_args {int /*<<< orphan*/  sig; int /*<<< orphan*/  set; } ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  set ;
struct TYPE_5__ {int /*<<< orphan*/  ksi_signo; } ;
typedef  TYPE_2__ ksiginfo_t ;
struct TYPE_4__ {scalar_t__ p_osrel; } ;

/* Variables and functions */
 int EINTR ; 
 int ERESTART ; 
 scalar_t__ P_OSREL_SIGWAIT ; 
 int copyin (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int kern_sigtimedwait (struct thread*,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *) ; 

int
sys_sigwait(struct thread *td, struct sigwait_args *uap)
{
	ksiginfo_t ksi;
	sigset_t set;
	int error;

	error = copyin(uap->set, &set, sizeof(set));
	if (error) {
		td->td_retval[0] = error;
		return (0);
	}

	error = kern_sigtimedwait(td, set, &ksi, NULL);
	if (error) {
		if (error == EINTR && td->td_proc->p_osrel < P_OSREL_SIGWAIT)
			error = ERESTART;
		if (error == ERESTART)
			return (error);
		td->td_retval[0] = error;
		return (0);
	}

	error = copyout(&ksi.ksi_signo, uap->sig, sizeof(ksi.ksi_signo));
	td->td_retval[0] = error;
	return (0);
}