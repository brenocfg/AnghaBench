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
struct thread {int dummy; } ;
struct proc {int p_nice; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int PRIO_MAX ; 
 int PRIO_MIN ; 
 int /*<<< orphan*/  PRIV_SCHED_SETPRIORITY ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int p_cansched (struct thread*,struct proc*) ; 
 scalar_t__ priv_check (struct thread*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sched_nice (struct proc*,int) ; 

__attribute__((used)) static int
donice(struct thread *td, struct proc *p, int n)
{
	int error;

	PROC_LOCK_ASSERT(p, MA_OWNED);
	if ((error = p_cansched(td, p)))
		return (error);
	if (n > PRIO_MAX)
		n = PRIO_MAX;
	if (n < PRIO_MIN)
		n = PRIO_MIN;
	if (n < p->p_nice && priv_check(td, PRIV_SCHED_SETPRIORITY) != 0)
		return (EACCES);
	sched_nice(p, n);
	return (0);
}