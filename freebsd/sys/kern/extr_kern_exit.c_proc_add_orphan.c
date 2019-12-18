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
struct proc {int p_flag; int /*<<< orphan*/  p_treeflag; int /*<<< orphan*/  p_orphans; } ;

/* Variables and functions */
 int /*<<< orphan*/  KASSERT (int,char*) ; 
 scalar_t__ LIST_EMPTY (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LIST_INSERT_AFTER (int /*<<< orphan*/ ,struct proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LIST_INSERT_HEAD (int /*<<< orphan*/ *,struct proc*,int /*<<< orphan*/ ) ; 
 int P_TRACED ; 
 int /*<<< orphan*/  P_TREE_FIRST_ORPHAN ; 
 int /*<<< orphan*/  P_TREE_ORPHANED ; 
 int /*<<< orphan*/  SX_XLOCKED ; 
 int /*<<< orphan*/  p_orphan ; 
 int /*<<< orphan*/  proctree_lock ; 
 int /*<<< orphan*/  sx_assert (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
proc_add_orphan(struct proc *child, struct proc *parent)
{

	sx_assert(&proctree_lock, SX_XLOCKED);
	KASSERT((child->p_flag & P_TRACED) != 0,
	    ("proc_add_orphan: not traced"));

	if (LIST_EMPTY(&parent->p_orphans)) {
		child->p_treeflag |= P_TREE_FIRST_ORPHAN;
		LIST_INSERT_HEAD(&parent->p_orphans, child, p_orphan);
	} else {
		LIST_INSERT_AFTER(LIST_FIRST(&parent->p_orphans),
		    child, p_orphan);
	}
	child->p_treeflag |= P_TREE_ORPHANED;
}