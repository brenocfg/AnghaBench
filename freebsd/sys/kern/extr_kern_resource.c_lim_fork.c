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
struct proc {scalar_t__ p_cpulimit; int /*<<< orphan*/  p_limco; int /*<<< orphan*/  p_mtx; int /*<<< orphan*/  p_limit; } ;

/* Variables and functions */
 int /*<<< orphan*/  C_PREL (int) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 scalar_t__ RLIM_INFINITY ; 
 int /*<<< orphan*/  SBT_1S ; 
 int /*<<< orphan*/  callout_init_mtx (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  callout_reset_sbt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lim_cb ; 
 int /*<<< orphan*/  lim_hold (int /*<<< orphan*/ ) ; 

void
lim_fork(struct proc *p1, struct proc *p2)
{

	PROC_LOCK_ASSERT(p1, MA_OWNED);
	PROC_LOCK_ASSERT(p2, MA_OWNED);

	p2->p_limit = lim_hold(p1->p_limit);
	callout_init_mtx(&p2->p_limco, &p2->p_mtx, 0);
	if (p1->p_cpulimit != RLIM_INFINITY)
		callout_reset_sbt(&p2->p_limco, SBT_1S, 0,
		    lim_cb, p2, C_PREL(1));
}