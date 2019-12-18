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
typedef  int /*<<< orphan*/  u32 ;
struct binder_ref_data {int dummy; } ;
struct binder_ref {struct binder_ref_data data; struct binder_node* node; } ;
struct binder_proc {int dummy; } ;
struct binder_node {int dummy; } ;

/* Variables and functions */
 struct binder_ref* binder_get_ref_olocked (struct binder_proc*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  binder_inc_node_tmpref (struct binder_node*) ; 
 int /*<<< orphan*/  binder_proc_lock (struct binder_proc*) ; 
 int /*<<< orphan*/  binder_proc_unlock (struct binder_proc*) ; 

__attribute__((used)) static struct binder_node *binder_get_node_from_ref(
		struct binder_proc *proc,
		u32 desc, bool need_strong_ref,
		struct binder_ref_data *rdata)
{
	struct binder_node *node;
	struct binder_ref *ref;

	binder_proc_lock(proc);
	ref = binder_get_ref_olocked(proc, desc, need_strong_ref);
	if (!ref)
		goto err_no_ref;
	node = ref->node;
	/*
	 * Take an implicit reference on the node to ensure
	 * it stays alive until the call to binder_put_node()
	 */
	binder_inc_node_tmpref(node);
	if (rdata)
		*rdata = ref->data;
	binder_proc_unlock(proc);

	return node;

err_no_ref:
	binder_proc_unlock(proc);
	return NULL;
}