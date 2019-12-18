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
struct proc {int p_flag; int /*<<< orphan*/  p_pid; int /*<<< orphan*/  p_oppid; struct proc* p_pptr; int /*<<< orphan*/  p_children; int /*<<< orphan*/  p_ksi; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_REMOVE (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MA_OWNED ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_LOCK_ASSERT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int P_TRACED ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  proc_add_orphan (struct proc*,struct proc*) ; 
 int /*<<< orphan*/  proc_clear_orphan (struct proc*) ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sigqueue_take (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
proc_reparent(struct proc *child, struct proc *parent, bool set_oppid)
{

	sx_assert(&proctree_lock, SX_XLOCKED);
	PROC_LOCK_ASSERT(child, MA_OWNED);
	if (child->p_pptr == parent)
		return;

	PROC_LOCK(child->p_pptr);
	sigqueue_take(child->p_ksi);
	PROC_UNLOCK(child->p_pptr);
	LIST_REMOVE(child, p_sibling);
	LIST_INSERT_HEAD(&parent->p_children, child, p_sibling);

	proc_clear_orphan(child);
	if ((child->p_flag & P_TRACED) != 0) {
		proc_add_orphan(child, child->p_pptr);
	}

	child->p_pptr = parent;
	if (set_oppid)
		child->p_oppid = parent->p_pid;
}