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
struct list_head {int dummy; } ;
struct binder_node {int dummy; } ;

/* Variables and functions */
 int binder_inc_node_nilocked (struct binder_node*,int,int,struct list_head*) ; 
 int /*<<< orphan*/  binder_node_inner_lock (struct binder_node*) ; 
 int /*<<< orphan*/  binder_node_inner_unlock (struct binder_node*) ; 

__attribute__((used)) static int binder_inc_node(struct binder_node *node, int strong, int internal,
			   struct list_head *target_list)
{
	int ret;

	binder_node_inner_lock(node);
	ret = binder_inc_node_nilocked(node, strong, internal, target_list);
	binder_node_inner_unlock(node);

	return ret;
}