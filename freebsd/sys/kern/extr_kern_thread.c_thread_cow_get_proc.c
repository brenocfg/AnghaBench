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
struct thread {int /*<<< orphan*/  td_cowgen; int /*<<< orphan*/  td_limit; int /*<<< orphan*/  td_ucred; } ;
struct proc {int /*<<< orphan*/  p_cowgen; int /*<<< orphan*/  p_limit; int /*<<< orphan*/  p_ucred; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  crhold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lim_hold (int /*<<< orphan*/ ) ; 

void
thread_cow_get_proc(struct thread *newtd, struct proc *p)
{

	PROC_LOCK_ASSERT(p, MA_OWNED);
	newtd->td_ucred = crhold(p->p_ucred);
	newtd->td_limit = lim_hold(p->p_limit);
	newtd->td_cowgen = p->p_cowgen;
}