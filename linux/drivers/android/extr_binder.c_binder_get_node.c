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
struct binder_proc {int dummy; } ;
struct binder_node {int dummy; } ;
typedef  int /*<<< orphan*/  binder_uintptr_t ;

/* Variables and functions */
 struct binder_node* binder_get_node_ilocked (struct binder_proc*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  binder_inner_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_inner_proc_unlock (struct binder_proc*) ; 

__attribute__((used)) static struct binder_node *binder_get_node(struct binder_proc *proc,
					   binder_uintptr_t ptr)
{
	struct binder_node *node;

	binder_inner_proc_lock(proc);
	node = binder_get_node_ilocked(proc, ptr);
	binder_inner_proc_unlock(proc);
	return node;
}