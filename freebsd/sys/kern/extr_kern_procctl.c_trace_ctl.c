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
struct proc {int p_flag; scalar_t__ p_traceflag; int p_flag2; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 int EPERM ; 
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int P2_NOTRACE ; 
 int P2_NOTRACE_EXEC ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
#define  PROC_TRACE_CTL_DISABLE 130 
#define  PROC_TRACE_CTL_DISABLE_EXEC 129 
#define  PROC_TRACE_CTL_ENABLE 128 
 int P_TRACED ; 

__attribute__((used)) static int
trace_ctl(struct thread *td, struct proc *p, int state)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);

	/*
	 * Ktrace changes p_traceflag from or to zero under the
	 * process lock, so the test does not need to acquire ktrace
	 * mutex.
	 */
	if ((p->p_flag & P_TRACED) != 0 || p->p_traceflag != 0)
		return (EBUSY);

	switch (state) {
	case PROC_TRACE_CTL_ENABLE:
		if (td->td_proc != p)
			return (EPERM);
		p->p_flag2 &= ~(P2_NOTRACE | P2_NOTRACE_EXEC);
		break;
	case PROC_TRACE_CTL_DISABLE_EXEC:
		p->p_flag2 |= P2_NOTRACE_EXEC | P2_NOTRACE;
		break;
	case PROC_TRACE_CTL_DISABLE:
		if ((p->p_flag2 & P2_NOTRACE_EXEC) != 0) {
			KASSERT((p->p_flag2 & P2_NOTRACE) != 0,
			    ("dandling P2_NOTRACE_EXEC"));
			if (td->td_proc != p)
				return (EPERM);
			p->p_flag2 &= ~P2_NOTRACE_EXEC;
		} else {
			p->p_flag2 |= P2_NOTRACE;
		}
		break;
	default:
		return (EINVAL);
	}
	return (0);
}