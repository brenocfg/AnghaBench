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
typedef  int /*<<< orphan*/  ts ;
struct timespec {int dummy; } ;
struct thread {int /*<<< orphan*/ * td_retval; } ;
struct sigtimedwait_args {int /*<<< orphan*/  info; scalar_t__ set; scalar_t__ timeout; } ;
typedef  struct timespec sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  set ;
struct TYPE_3__ {int /*<<< orphan*/  ksi_signo; int /*<<< orphan*/  ksi_info; } ;
typedef  TYPE_1__ ksiginfo_t ;

/* Variables and functions */
 int copyin (scalar_t__,struct timespec*,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int kern_sigtimedwait (struct thread*,struct timespec,TYPE_1__*,struct timespec*) ; 

int
sys_sigtimedwait(struct thread *td, struct sigtimedwait_args *uap)
{
	struct timespec ts;
	struct timespec *timeout;
	sigset_t set;
	ksiginfo_t ksi;
	int error;

	if (uap->timeout) {
		error = copyin(uap->timeout, &ts, sizeof(ts));
		if (error)
			return (error);

		timeout = &ts;
	} else
		timeout = NULL;

	error = copyin(uap->set, &set, sizeof(set));
	if (error)
		return (error);

	error = kern_sigtimedwait(td, set, &ksi, timeout);
	if (error)
		return (error);

	if (uap->info)
		error = copyout(&ksi.ksi_info, uap->info, sizeof(siginfo_t));

	if (error == 0)
		td->td_retval[0] = ksi.ksi_signo;
	return (error);
}