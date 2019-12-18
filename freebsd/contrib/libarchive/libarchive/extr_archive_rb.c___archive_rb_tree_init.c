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
struct archive_rb_tree_ops {int dummy; } ;
struct archive_rb_tree {int /*<<< orphan*/  rbt_root; struct archive_rb_tree_ops const* rbt_ops; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 struct archive_rb_node* RB_SENTINEL_NODE ; 

void
__archive_rb_tree_init(struct archive_rb_tree *rbt,
    const struct archive_rb_tree_ops *ops)
{
	rbt->rbt_ops = ops;
	*((struct archive_rb_node **)&rbt->rbt_root) = RB_SENTINEL_NODE;
}