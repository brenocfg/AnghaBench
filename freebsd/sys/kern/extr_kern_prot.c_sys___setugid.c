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
struct thread {struct proc* td_proc; } ;
struct proc {int /*<<< orphan*/  p_flag; } ;
struct __setugid_args {int flag; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOSYS ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  P_SUGID ; 

int
sys___setugid(struct thread *td, struct __setugid_args *uap)
{
#ifdef REGRESSION
	struct proc *p;

	p = td->td_proc;
	switch (uap->flag) {
	case 0:
		PROC_LOCK(p);
		p->p_flag &= ~P_SUGID;
		PROC_UNLOCK(p);
		return (0);
	case 1:
		PROC_LOCK(p);
		p->p_flag |= P_SUGID;
		PROC_UNLOCK(p);
		return (0);
	default:
		return (EINVAL);
	}
#else /* !REGRESSION */

	return (ENOSYS);
#endif /* REGRESSION */
}