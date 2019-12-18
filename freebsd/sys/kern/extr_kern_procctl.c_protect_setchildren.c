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
struct proc {struct proc* p_pptr; int /*<<< orphan*/  p_children; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_EMPTY (int /*<<< orphan*/ *) ; 
 struct proc* LIST_FIRST (int /*<<< orphan*/ *) ; 
 struct proc* LIST_NEXT (struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_LOCK (struct proc*) ; 
 int /*<<< orphan*/  PROC_UNLOCK (struct proc*) ; 
 int /*<<< orphan*/  SX_LOCKED ; 
 int /*<<< orphan*/  p_sibling ; 
 int /*<<< orphan*/  proctree_lock ; 
 int protect_setchild (struct thread*,struct proc*,int) ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
protect_setchildren(struct thread *td, struct proc *top, int flags)
{
	struct proc *p;
	int ret;

	p = top;
	ret = 0;
	sx_assert(&proctree_lock, SX_LOCKED);
	for (;;) {
		ret |= protect_setchild(td, p, flags);
		PROC_UNLOCK(p);
		/*
		 * If this process has children, descend to them next,
		 * otherwise do any siblings, and if done with this level,
		 * follow back up the tree (but not past top).
		 */
		if (!LIST_EMPTY(&p->p_children))
			p = LIST_FIRST(&p->p_children);
		else for (;;) {
			if (p == top) {
				PROC_LOCK(p);
				return (ret);
			}
			if (LIST_NEXT(p, p_sibling)) {
				p = LIST_NEXT(p, p_sibling);
				break;
			}
			p = p->p_pptr;
		}
		PROC_LOCK(p);
	}
}