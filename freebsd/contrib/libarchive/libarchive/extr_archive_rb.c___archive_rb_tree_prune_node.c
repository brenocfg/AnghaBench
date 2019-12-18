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
struct archive_rb_tree {int dummy; } ;
struct archive_rb_node {int /*<<< orphan*/  rb_left; int /*<<< orphan*/ * rb_nodes; } ;

/* Variables and functions */
 struct archive_rb_node* RB_FATHER (struct archive_rb_node*) ; 
 unsigned int RB_POSITION (struct archive_rb_node*) ; 
 int /*<<< orphan*/  __archive_rb_tree_removal_rebalance (struct archive_rb_tree*,struct archive_rb_node*,unsigned int const) ; 

__attribute__((used)) static void
__archive_rb_tree_prune_node(struct archive_rb_tree *rbt,
    struct archive_rb_node *self, int rebalance)
{
	const unsigned int which = RB_POSITION(self);
	struct archive_rb_node *father = RB_FATHER(self);

	/*
	 * Since we are childless, we know that self->rb_left is pointing
	 * to the sentinel node.
	 */
	father->rb_nodes[which] = self->rb_left;

	/*
	 * Rebalance if requested.
	 */
	if (rebalance)
		__archive_rb_tree_removal_rebalance(rbt, father, which);
}