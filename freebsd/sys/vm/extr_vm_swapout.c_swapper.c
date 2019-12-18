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
struct proc {scalar_t__ p_state; int p_flag; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 scalar_t__ PRS_NORMAL ; 
 int /*<<< orphan*/  PVM ; 
 int P_INMEM ; 
 int P_SWAPPINGIN ; 
 int P_SWAPPINGOUT ; 
 int /*<<< orphan*/  SWAPIN_INTERVAL ; 
 int /*<<< orphan*/  allproc_lock ; 
 int /*<<< orphan*/  faultin (struct proc*) ; 
 int /*<<< orphan*/  proc0 ; 
 struct proc* swapper_selector (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapper_wkilled_only () ; 
 int /*<<< orphan*/  sx_slock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sx_sunlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tsleep (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void
swapper(void)
{
	struct proc *p;

	for (;;) {
		sx_slock(&allproc_lock);
		p = swapper_selector(swapper_wkilled_only());
		sx_sunlock(&allproc_lock);

		if (p == NULL) {
			tsleep(&proc0, PVM, "swapin", SWAPIN_INTERVAL);
		} else {
			PROC_LOCK_ASSERT(p, MA_OWNED);

			/*
			 * Another process may be bringing or may have
			 * already brought this process in while we
			 * traverse all threads.  Or, this process may
			 * have exited or even being swapped out
			 * again.
			 */
			if (p->p_state == PRS_NORMAL && (p->p_flag & (P_INMEM |
			    P_SWAPPINGOUT | P_SWAPPINGIN)) == 0) {
				faultin(p);
			}
			PROC_UNLOCK(p);
		}
	}
}