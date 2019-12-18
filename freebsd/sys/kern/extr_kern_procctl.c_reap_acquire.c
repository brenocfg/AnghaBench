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
struct proc {int p_treeflag; } ;

/* Variables and functions */
 int EBUSY ; 
 int EPERM ; 
 int P_TREE_REAPER ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 struct proc* curproc ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
reap_acquire(struct thread *td, struct proc *p)
{

	sx_assert(&proctree_lock, SX_XLOCKED);
	if (p != curproc)
		return (EPERM);
	if ((p->p_treeflag & P_TREE_REAPER) != 0)
		return (EBUSY);
	p->p_treeflag |= P_TREE_REAPER;
	/*
	 * We do not reattach existing children and the whole tree
	 * under them to us, since p->p_reaper already seen them.
	 */
	return (0);
}