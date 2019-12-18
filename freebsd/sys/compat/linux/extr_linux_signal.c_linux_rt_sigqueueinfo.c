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
struct thread {int dummy; } ;
struct proc {int dummy; } ;
struct linux_rt_sigqueueinfo_args {int /*<<< orphan*/  pid; int /*<<< orphan*/  sig; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  linfo ;
struct TYPE_4__ {scalar_t__ lsi_code; } ;
typedef  TYPE_1__ l_siginfo_t ;
typedef  int /*<<< orphan*/  ksiginfo_t ;

/* Variables and functions */
 int EINVAL ; 
 int EPERM ; 
 int ESRCH ; 
 int /*<<< orphan*/  LINUX_SIG_VALID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int copyin (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ksiginfo_init (int /*<<< orphan*/ *) ; 
 int linux_to_bsd_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsiginfo_to_ksiginfo (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int p_cansignal (struct thread*,struct proc*,int) ; 
 struct proc* pfind_any (int /*<<< orphan*/ ) ; 
 int tdsendsignal (struct proc*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

int
linux_rt_sigqueueinfo(struct thread *td, struct linux_rt_sigqueueinfo_args *args)
{
	l_siginfo_t linfo;
	struct proc *p;
	ksiginfo_t ksi;
	int error;
	int sig;

	if (!LINUX_SIG_VALID(args->sig))
		return (EINVAL);

	error = copyin(args->info, &linfo, sizeof(linfo));
	if (error != 0)
		return (error);

	if (linfo.lsi_code >= 0)
		return (EPERM);

	sig = linux_to_bsd_signal(args->sig);

	error = ESRCH;
	if ((p = pfind_any(args->pid)) != NULL) {
		error = p_cansignal(td, p, sig);
		if (error != 0) {
			PROC_UNLOCK(p);
			return (error);
		}

		ksiginfo_init(&ksi);
		lsiginfo_to_ksiginfo(&linfo, &ksi, sig);
		error = tdsendsignal(p, NULL, sig, &ksi);
		PROC_UNLOCK(p);
	}

	return (error);
}