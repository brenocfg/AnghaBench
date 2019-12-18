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
struct binder_node {scalar_t__ proc; } ;

/* Variables and functions */
 int /*<<< orphan*/  binder_dead_nodes_lock ; 
 int /*<<< orphan*/  binder_inc_node_tmpref_ilocked (struct binder_node*) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (scalar_t__) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (scalar_t__) ; 
 int /*<<< orphan*/  binder_node_lock (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_unlock (struct binder_node*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void binder_inc_node_tmpref(struct binder_node *node)
{
	binder_node_lock(node);
	if (node->proc)
		binder_inner_proc_lock(node->proc);
	else
		spin_lock(&binder_dead_nodes_lock);
	binder_inc_node_tmpref_ilocked(node);
	if (node->proc)
		binder_inner_proc_unlock(node->proc);
	else
		spin_unlock(&binder_dead_nodes_lock);
	binder_node_unlock(node);
}