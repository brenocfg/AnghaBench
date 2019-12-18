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
struct TYPE_4__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct thread {int /*<<< orphan*/  td_proc; int /*<<< orphan*/  td_sigmask; } ;
struct getcontext_args {int /*<<< orphan*/ * ucp; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GET_MC_CLEAR_RET ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UC_COPY_SIZE ; 
 int /*<<< orphan*/  bzero (TYPE_1__*,int) ; 
 int copyout (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_mcontext (struct thread*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
sys_getcontext(struct thread *td, struct getcontext_args *uap)
{
	ucontext_t uc;
	int ret;

	if (uap->ucp == NULL)
		ret = EINVAL;
	else {
		bzero(&uc, sizeof(ucontext_t));
		get_mcontext(td, &uc.uc_mcontext, GET_MC_CLEAR_RET);
		PROC_LOCK(td->td_proc);
		uc.uc_sigmask = td->td_sigmask;
		PROC_UNLOCK(td->td_proc);
		ret = copyout(&uc, uap->ucp, UC_COPY_SIZE);
	}
	return (ret);
}