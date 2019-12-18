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
struct proc {scalar_t__ p_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 struct proc* curproc ; 
 struct proc* proc_realparent (struct proc*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int
inferior(struct proc *p)
{

	sx_assert(&proctree_lock, SX_LOCKED);
	PROC_LOCK_ASSERT(p, MA_OWNED);
	for (; p != curproc; p = proc_realparent(p)) {
		if (p->p_pid == 0)
			return (0);
	}
	return (1);
}