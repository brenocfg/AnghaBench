#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct thread {TYPE_1__* td_limit; struct proc* td_proc; } ;
struct rlimit {int dummy; } ;
struct proc {TYPE_2__* p_sysent; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sv_fixlimit ) (struct rlimit*,int) ;} ;
struct TYPE_3__ {struct rlimit* pl_rlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MPASS (int) ; 
 int RLIM_NLIMITS ; 
 struct thread* curthread ; 
 int /*<<< orphan*/  stub1 (struct rlimit*,int) ; 

void
lim_rlimit(struct thread *td, int which, struct rlimit *rlp)
{
	struct proc *p = td->td_proc;

	MPASS(td == curthread);
	KASSERT(which >= 0 && which < RLIM_NLIMITS,
	    ("request for invalid resource limit"));
	*rlp = td->td_limit->pl_rlimit[which];
	if (p->p_sysent->sv_fixlimit != NULL)
		p->p_sysent->sv_fixlimit(rlp, which);
}