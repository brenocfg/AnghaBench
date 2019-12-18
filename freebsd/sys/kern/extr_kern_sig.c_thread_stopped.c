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
struct proc {int p_suspcount; int p_flag; int p_numthreads; int /*<<< orphan*/  p_pptr; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLD_STOPPED ; 
 int /*<<< orphan*/  CLD_TRAPPED ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_SLOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_SUNLOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (int /*<<< orphan*/ ) ; 
 int P_STOPPED_SIG ; 
 int P_TRACED ; 
 int P_WAITED ; 
 int /*<<< orphan*/  childproc_stopped (struct proc*,int /*<<< orphan*/ ) ; 
 struct proc* curproc ; 

void
thread_stopped(struct proc *p)
{
	int n;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	PROC_SLOCK_ASSERT(p, MA_OWNED);
	n = p->p_suspcount;
	if (p == curproc)
		n++;
	if ((p->p_flag & P_STOPPED_SIG) && (n == p->p_numthreads)) {
		PROC_SUNLOCK(p);
		p->p_flag &= ~P_WAITED;
		PROC_LOCK(p->p_pptr);
		childproc_stopped(p, (p->p_flag & P_TRACED) ?
			CLD_TRAPPED : CLD_STOPPED);
		PROC_UNLOCK(p->p_pptr);
		PROC_SLOCK(p);
	}
}