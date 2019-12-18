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
typedef  int /*<<< orphan*/  uc ;
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_sigmask; } ;
struct ia32_ucontext {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_mcontext; } ;
struct freebsd32_swapcontext_args {int /*<<< orphan*/ * ucp; int /*<<< orphan*/ * oucp; } ;

/* Variables and functions */
 int EINVAL ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  UC_COPY_SIZE ; 
 int /*<<< orphan*/  bzero (struct ia32_ucontext*,int) ; 
 int copyin (int /*<<< orphan*/ *,struct ia32_ucontext*,int /*<<< orphan*/ ) ; 
 int copyout (struct ia32_ucontext*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ia32_get_mcontext (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ia32_set_mcontext (struct thread*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
freebsd32_swapcontext(struct thread *td, struct freebsd32_swapcontext_args *uap)
{
	struct ia32_ucontext uc;
	int ret;

	if (uap->oucp == NULL || uap->ucp == NULL)
		ret = EINVAL;
	else {
		bzero(&uc, sizeof(uc));
		ia32_get_mcontext(td, &uc.uc_mcontext, GET_MC_CLEAR_RET);
		PROC_LOCK(td->td_proc);
		uc.uc_sigmask = td->td_sigmask;
		PROC_UNLOCK(td->td_proc);
		ret = copyout(&uc, uap->oucp, UC_COPY_SIZE);
		if (ret == 0) {
			ret = copyin(uap->ucp, &uc, UC_COPY_SIZE);
			if (ret == 0) {
				ret = ia32_set_mcontext(td, &uc.uc_mcontext);
				if (ret == 0) {
					kern_sigprocmask(td, SIG_SETMASK,
					    &uc.uc_sigmask, NULL, 0);
				}
			}
		}
	}
	return (ret == 0 ? EJUSTRETURN : ret);
}