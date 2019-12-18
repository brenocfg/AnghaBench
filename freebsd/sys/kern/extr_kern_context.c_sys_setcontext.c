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
struct TYPE_3__ {int /*<<< orphan*/  uc_sigmask; int /*<<< orphan*/  uc_mcontext; } ;
typedef  TYPE_1__ ucontext_t ;
struct thread {int dummy; } ;
struct setcontext_args {int /*<<< orphan*/ * ucp; } ;

/* Variables and functions */
 int EINVAL ; 
 int EJUSTRETURN ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  UC_COPY_SIZE ; 
 int copyin (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kern_sigprocmask (struct thread*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int set_mcontext (struct thread*,int /*<<< orphan*/ *) ; 

int
sys_setcontext(struct thread *td, struct setcontext_args *uap)
{
	ucontext_t uc;
	int ret;

	if (uap->ucp == NULL)
		ret = EINVAL;
	else {
		ret = copyin(uap->ucp, &uc, UC_COPY_SIZE);
		if (ret == 0) {
			ret = set_mcontext(td, &uc.uc_mcontext);
			if (ret == 0) {
				kern_sigprocmask(td, SIG_SETMASK, &uc.uc_sigmask,
				    NULL, 0);
			}
		}
	}
	return (ret == 0 ? EJUSTRETURN : ret);
}