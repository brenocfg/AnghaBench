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
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 scalar_t__ RB_BLACK_P (struct archive_rb_node*) ; 
 scalar_t__ RB_CHILDLESS_P (struct archive_rb_node*) ; 
 unsigned int RB_DIR_LEFT ; 
 unsigned int RB_DIR_OTHER ; 
 unsigned int RB_DIR_RIGHT ; 
 scalar_t__ RB_LEFT_SENTINEL_P (struct archive_rb_node*) ; 
 unsigned int RB_POSITION (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_ROOT_P (struct archive_rb_tree*,struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_TWOCHILDREN_P (struct archive_rb_node*) ; 
 struct archive_rb_node* __archive_rb_tree_iterate (struct archive_rb_tree*,struct archive_rb_node*,unsigned int) ; 
 int /*<<< orphan*/  __archive_rb_tree_prune_blackred_branch (struct archive_rb_node*,unsigned int) ; 
 int /*<<< orphan*/  __archive_rb_tree_prune_node (struct archive_rb_tree*,struct archive_rb_node*,int const) ; 
 int /*<<< orphan*/  __archive_rb_tree_swap_prune_and_rebalance (struct archive_rb_tree*,struct archive_rb_node*,struct archive_rb_node*) ; 

void
__archive_rb_tree_remove_node(struct archive_rb_tree *rbt,
    struct archive_rb_node *self)
{
	struct archive_rb_node *standin;
	unsigned int which;

	/*
	 * In the following diagrams, we (the node to be removed) are S.  Red
	 * nodes are lowercase.  T could be either red or black.
	 *
	 * Remember the major axiom of the red-black tree: the number of
	 * black nodes from the root to each leaf is constant across all
	 * leaves, only the number of red nodes varies.
	 *
	 * Thus removing a red leaf doesn't require any other changes to a
	 * red-black tree.  So if we must remove a node, attempt to rearrange
	 * the tree so we can remove a red node.
	 *
	 * The simplest case is a childless red node or a childless root node:
	 *
	 * |    T  -->    T  |    or    |  R  -->  *  |
	 * |  s    -->  *    |
	 */
	if (RB_CHILDLESS_P(self)) {
		const int rebalance = RB_BLACK_P(self) && !RB_ROOT_P(rbt, self);
		__archive_rb_tree_prune_node(rbt, self, rebalance);
		return;
	}
	if (!RB_TWOCHILDREN_P(self)) {
		/*
		 * The next simplest case is the node we are deleting is
		 * black and has one red child.
		 *
		 * |      T  -->      T  -->      T  |
		 * |    S    -->  R      -->  R      |
		 * |  r      -->    s    -->    *    |
		 */
		which = RB_LEFT_SENTINEL_P(self) ? RB_DIR_RIGHT : RB_DIR_LEFT;
		__archive_rb_tree_prune_blackred_branch(self, which);
		return;
	}

	/*
	 * We invert these because we prefer to remove from the inside of
	 * the tree.
	 */
	which = RB_POSITION(self) ^ RB_DIR_OTHER;

	/*
	 * Let's find the node closes to us opposite of our parent
	 * Now swap it with ourself, "prune" it, and rebalance, if needed.
	 */
	standin = __archive_rb_tree_iterate(rbt, self, which);
	__archive_rb_tree_swap_prune_and_rebalance(rbt, self, standin);
}