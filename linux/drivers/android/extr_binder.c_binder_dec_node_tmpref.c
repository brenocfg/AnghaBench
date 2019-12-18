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
struct binder_node {scalar_t__ tmp_refs; int /*<<< orphan*/  proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __acquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  binder_dead_nodes_lock ; 
 int binder_dec_node_nilocked (struct binder_node*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  binder_free_node (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_inner_lock (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_inner_unlock (struct binder_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_dec_node_tmpref(struct binder_node *node)
{
	bool free_node;

	binder_node_inner_lock(node);
	if (!node->proc)
		spin_lock(&binder_dead_nodes_lock);
	else
		__acquire(&binder_dead_nodes_lock);
	node->tmp_refs--;
	BUG_ON(node->tmp_refs < 0);
	if (!node->proc)
		spin_unlock(&binder_dead_nodes_lock);
	else
		__release(&binder_dead_nodes_lock);
	/*
	 * Call binder_dec_node() to check if all refcounts are 0
	 * and cleanup is needed. Calling with strong=0 and internal=1
	 * causes no actual reference to be released in binder_dec_node().
	 * If that changes, a change is needed here too.
	 */
	free_node = binder_dec_node_nilocked(node, 0, 1);
	binder_node_inner_unlock(node);
	if (free_node)
		binder_free_node(node);
}