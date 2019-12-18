#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct binder_proc {int /*<<< orphan*/  nodes; int /*<<< orphan*/  todo; int /*<<< orphan*/  inner_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  entry; } ;
struct binder_node {int /*<<< orphan*/  debug_id; int /*<<< orphan*/  dead_node; scalar_t__ tmp_refs; TYPE_1__ work; int /*<<< orphan*/  rb_node; scalar_t__ local_weak_refs; scalar_t__ local_strong_refs; int /*<<< orphan*/  refs; scalar_t__ has_weak_ref; scalar_t__ has_strong_ref; scalar_t__ internal_strong_refs; int /*<<< orphan*/  lock; struct binder_proc* proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BINDER_DEBUG_INTERNAL_REFS ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  assert_spin_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_dead_nodes_lock ; 
 int /*<<< orphan*/  binder_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_dequeue_work_ilocked (TYPE_1__*) ; 
 int /*<<< orphan*/  binder_enqueue_work_ilocked (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_wakeup_proc_ilocked (struct binder_proc*) ; 
 int /*<<< orphan*/  hlist_del (int /*<<< orphan*/ *) ; 
 scalar_t__ hlist_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool binder_dec_node_nilocked(struct binder_node *node,
				     int strong, int internal)
{
	struct binder_proc *proc = node->proc;

	assert_spin_locked(&node->lock);
	if (proc)
		assert_spin_locked(&proc->inner_lock);
	if (strong) {
		if (internal)
			node->internal_strong_refs--;
		else
			node->local_strong_refs--;
		if (node->local_strong_refs || node->internal_strong_refs)
			return false;
	} else {
		if (!internal)
			node->local_weak_refs--;
		if (node->local_weak_refs || node->tmp_refs ||
				!hlist_empty(&node->refs))
			return false;
	}

	if (proc && (node->has_strong_ref || node->has_weak_ref)) {
		if (list_empty(&node->work.entry)) {
			binder_enqueue_work_ilocked(&node->work, &proc->todo);
			binder_wakeup_proc_ilocked(proc);
		}
	} else {
		if (hlist_empty(&node->refs) && !node->local_strong_refs &&
		    !node->local_weak_refs && !node->tmp_refs) {
			if (proc) {
				binder_dequeue_work_ilocked(&node->work);
				rb_erase(&node->rb_node, &proc->nodes);
				binder_debug(BINDER_DEBUG_INTERNAL_REFS,
					     "refless node %d deleted\n",
					     node->debug_id);
			} else {
				BUG_ON(!list_empty(&node->work.entry));
				spin_lock(&binder_dead_nodes_lock);
				/*
				 * tmp_refs could have changed so
				 * check it again
				 */
				if (node->tmp_refs) {
					spin_unlock(&binder_dead_nodes_lock);
					return false;
				}
				hlist_del(&node->dead_node);
				spin_unlock(&binder_dead_nodes_lock);
				binder_debug(BINDER_DEBUG_INTERNAL_REFS,
					     "dead node %d deleted\n",
					     node->debug_id);
			}
			return true;
		}
	}
	return false;
}