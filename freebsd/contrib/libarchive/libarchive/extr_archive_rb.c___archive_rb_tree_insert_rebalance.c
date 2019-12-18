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
struct archive_rb_tree {struct archive_rb_node* rbt_root; } ;
struct archive_rb_node {struct archive_rb_node** rb_nodes; struct archive_rb_node* rb_right; } ;

/* Variables and functions */
 scalar_t__ RB_BLACK_P (struct archive_rb_node*) ; 
 unsigned int RB_DIR_OTHER ; 
 struct archive_rb_node* RB_FATHER (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_MARK_BLACK (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_MARK_RED (struct archive_rb_node*) ; 
 scalar_t__ RB_ROOT_P (struct archive_rb_tree*,struct archive_rb_node*) ; 
 int /*<<< orphan*/  __archive_rb_tree_reparent_nodes (struct archive_rb_node*,unsigned int) ; 

__attribute__((used)) static void
__archive_rb_tree_insert_rebalance(struct archive_rb_tree *rbt,
    struct archive_rb_node *self)
{
	struct archive_rb_node * father = RB_FATHER(self);
	struct archive_rb_node * grandpa;
	struct archive_rb_node * uncle;
	unsigned int which;
	unsigned int other;

	for (;;) {
		/*
		 * We are red and our parent is red, therefore we must have a
		 * grandfather and he must be black.
		 */
		grandpa = RB_FATHER(father);
		which = (father == grandpa->rb_right);
		other = which ^ RB_DIR_OTHER;
		uncle = grandpa->rb_nodes[other];

		if (RB_BLACK_P(uncle))
			break;

		/*
		 * Case 1: our uncle is red
		 *   Simply invert the colors of our parent and
		 *   uncle and make our grandparent red.  And
		 *   then solve the problem up at his level.
		 */
		RB_MARK_BLACK(uncle);
		RB_MARK_BLACK(father);
		if (RB_ROOT_P(rbt, grandpa)) {
			/*
			 * If our grandpa is root, don't bother
			 * setting him to red, just return.
			 */
			return;
		}
		RB_MARK_RED(grandpa);
		self = grandpa;
		father = RB_FATHER(self);
		if (RB_BLACK_P(father)) {
			/*
			 * If our great-grandpa is black, we're done.
			 */
			return;
		}
	}

	/*
	 * Case 2&3: our uncle is black.
	 */
	if (self == father->rb_nodes[other]) {
		/*
		 * Case 2: we are on the same side as our uncle
		 *   Swap ourselves with our parent so this case
		 *   becomes case 3.  Basically our parent becomes our
		 *   child.
		 */
		__archive_rb_tree_reparent_nodes(father, other);
	}
	/*
	 * Case 3: we are opposite a child of a black uncle.
	 *   Swap our parent and grandparent.  Since our grandfather
	 *   is black, our father will become black and our new sibling
	 *   (former grandparent) will become red.
	 */
	__archive_rb_tree_reparent_nodes(grandpa, which);

	/*
	 * Final step: Set the root to black.
	 */
	RB_MARK_BLACK(rbt->rbt_root);
}