#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int ss_flags; scalar_t__ ss_size; } ;
struct thread {int td_pflags; TYPE_2__ td_sigstk; struct proc* td_proc; } ;
struct proc {TYPE_1__* p_sysent; } ;
typedef  TYPE_2__ stack_t ;
struct TYPE_5__ {scalar_t__ sv_minsigstksz; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EPERM ; 
 int SS_DISABLE ; 
 int SS_ONSTACK ; 
 int TDP_ALTSTACK ; 
 int /*<<< orphan*/  cpu_getstack (struct thread*) ; 
 int sigonstack (int /*<<< orphan*/ ) ; 

int
kern_sigaltstack(struct thread *td, stack_t *ss, stack_t *oss)
{
	struct proc *p = td->td_proc;
	int oonstack;

	oonstack = sigonstack(cpu_getstack(td));

	if (oss != NULL) {
		*oss = td->td_sigstk;
		oss->ss_flags = (td->td_pflags & TDP_ALTSTACK)
		    ? ((oonstack) ? SS_ONSTACK : 0) : SS_DISABLE;
	}

	if (ss != NULL) {
		if (oonstack)
			return (EPERM);
		if ((ss->ss_flags & ~SS_DISABLE) != 0)
			return (EINVAL);
		if (!(ss->ss_flags & SS_DISABLE)) {
			if (ss->ss_size < p->p_sysent->sv_minsigstksz)
				return (ENOMEM);

			td->td_sigstk = *ss;
			td->td_pflags |= TDP_ALTSTACK;
		} else {
			td->td_pflags &= ~TDP_ALTSTACK;
		}
	}
	return (0);
}