#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_mcontext; } ;
typedef  TYPE_1__ ucontext32_t ;
typedef  int /*<<< orphan*/  uc ;
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_sigmask; } ;
struct freebsd32_swapcontext_args {int /*<<< orphan*/ * ucp; int /*<<< orphan*/ * oucp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  UC32_COPY_SIZE ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int copyin (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int copyout (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mcontext32 (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int set_mcontext32 (struct thread*,int /*<<< orphan*/ *) ; 

int
freebsd32_swapcontext(struct thread *td, struct freebsd32_swapcontext_args *uap)
{
	ucontext32_t uc;
	int ret;

	if (uap->oucp == NULL || uap->ucp == NULL)
		ret = EINVAL;
	else {
		bzero(&uc, sizeof(uc));
		get_mcontext32(td, &uc.uc_mcontext, GET_MC_CLEAR_RET);
		PROC_LOCK(td->td_proc);
		uc.uc_sigmask = td->td_sigmask;
		PROC_UNLOCK(td->td_proc);
		ret = copyout(&uc, uap->oucp, UC32_COPY_SIZE);
		if (ret == 0) {
			ret = copyin(uap->ucp, &uc, UC32_COPY_SIZE);
			if (ret == 0) {
				ret = set_mcontext32(td, &uc.uc_mcontext);
				kern_sigprocmask(td, SIG_SETMASK,
						&uc.uc_sigmask, NULL, 0);
			}
		}
	}
	return (ret);
}