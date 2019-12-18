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
struct rlimit {int dummy; } ;
struct proc {TYPE_2__* p_sysent; TYPE_1__* p_limit; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* sv_fixlimit ) (struct rlimit*,int) ;} ;
struct TYPE_3__ {struct rlimit* pl_rlimit; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int RLIM_NLIMITS ; 
 int /*<<< orphan*/  stub1 (struct rlimit*,int) ; 

void
lim_rlimit_proc(struct proc *p, int which, struct rlimit *rlp)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	KASSERT(which >= 0 && which < RLIM_NLIMITS,
	    ("request for invalid resource limit"));
	*rlp = p->p_limit->pl_rlimit[which];
	if (p->p_sysent->sv_fixlimit != NULL)
		p->p_sysent->sv_fixlimit(rlp, which);
}