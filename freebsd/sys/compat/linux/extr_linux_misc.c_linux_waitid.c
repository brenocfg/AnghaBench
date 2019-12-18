#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct thread {scalar_t__* td_retval; struct proc* td_proc; } ;
struct proc {int dummy; } ;
struct linux_waitid_args {int idtype; int /*<<< orphan*/ * info; int /*<<< orphan*/ * rusage; int /*<<< orphan*/  id; int /*<<< orphan*/  options; } ;
struct __wrusage {int /*<<< orphan*/  wru_children; } ;
struct TYPE_4__ {int /*<<< orphan*/  si_signo; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  lsi ;
typedef  int /*<<< orphan*/  l_siginfo_t ;
typedef  int /*<<< orphan*/  idtype_t ;

/* Variables and functions */
 int EINVAL ; 
#define  LINUX_P_ALL 130 
#define  LINUX_P_PGID 129 
#define  LINUX_P_PID 128 
 int /*<<< orphan*/  P_ALL ; 
 int /*<<< orphan*/  P_PGID ; 
 int /*<<< orphan*/  P_PID ; 
 int WCONTINUED ; 
 int WEXITED ; 
 int WNOHANG ; 
 int WNOWAIT ; 
 int WUNTRACED ; 
 int bsd_to_linux_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int copyout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int kern_wait6 (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int,struct __wrusage*,TYPE_1__*) ; 
 int linux_copyout_rusage (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  linux_to_bsd_waitopts (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  siginfo_to_lsiginfo (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

int
linux_waitid(struct thread *td, struct linux_waitid_args *args)
{
	int status, options, sig;
	struct __wrusage wru;
	siginfo_t siginfo;
	l_siginfo_t lsi;
	idtype_t idtype;
	struct proc *p;
	int error;

	options = 0;
	linux_to_bsd_waitopts(args->options, &options);

	if (options & ~(WNOHANG | WNOWAIT | WEXITED | WUNTRACED | WCONTINUED))
		return (EINVAL);
	if (!(options & (WEXITED | WUNTRACED | WCONTINUED)))
		return (EINVAL);

	switch (args->idtype) {
	case LINUX_P_ALL:
		idtype = P_ALL;
		break;
	case LINUX_P_PID:
		if (args->id <= 0)
			return (EINVAL);
		idtype = P_PID;
		break;
	case LINUX_P_PGID:
		if (args->id <= 0)
			return (EINVAL);
		idtype = P_PGID;
		break;
	default:
		return (EINVAL);
	}

	error = kern_wait6(td, idtype, args->id, &status, options,
	    &wru, &siginfo);
	if (error != 0)
		return (error);
	if (args->rusage != NULL) {
		error = linux_copyout_rusage(&wru.wru_children,
		    args->rusage);
		if (error != 0)
			return (error);
	}
	if (args->info != NULL) {
		p = td->td_proc;
		bzero(&lsi, sizeof(lsi));
		if (td->td_retval[0] != 0) {
			sig = bsd_to_linux_signal(siginfo.si_signo);
			siginfo_to_lsiginfo(&siginfo, &lsi, sig);
		}
		error = copyout(&lsi, args->info, sizeof(lsi));
	}
	td->td_retval[0] = 0;

	return (error);
}