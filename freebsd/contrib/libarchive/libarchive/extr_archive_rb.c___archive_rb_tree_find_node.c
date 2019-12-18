#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct archive_rb_tree {struct archive_rb_node* rbt_root; TYPE_1__* rbt_ops; } ;
struct archive_rb_node {struct archive_rb_node** rb_nodes; } ;
typedef  int (* archive_rbto_compare_key_fn ) (struct archive_rb_node*,void const*) ;
struct TYPE_2__ {int (* rbto_compare_key ) (struct archive_rb_node*,void const*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RB_SENTINEL_P (struct archive_rb_node*) ; 
 int stub1 (struct archive_rb_node*,void const*) ; 

struct archive_rb_node *
__archive_rb_tree_find_node(struct archive_rb_tree *rbt, const void *key)
{
	archive_rbto_compare_key_fn compare_key = rbt->rbt_ops->rbto_compare_key;
	struct archive_rb_node *parent = rbt->rbt_root;

	while (!RB_SENTINEL_P(parent)) {
		const signed int diff = (*compare_key)(parent, key);
		if (diff == 0)
			return parent;
		parent = parent->rb_nodes[diff > 0];
	}

	return NULL;
}