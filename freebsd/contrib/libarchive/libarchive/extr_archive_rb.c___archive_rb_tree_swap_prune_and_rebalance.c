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
struct archive_rb_node {struct archive_rb_node** rb_nodes; } ;

/* Variables and functions */
 int F ; 
 int RB_BLACK_P (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_COPY_PROPERTIES (struct archive_rb_node*,struct archive_rb_node*) ; 
 unsigned int const RB_DIR_OTHER ; 
 struct archive_rb_node* RB_FATHER (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_MARK_BLACK (struct archive_rb_node*) ; 
 size_t RB_POSITION (struct archive_rb_node*) ; 
 scalar_t__ RB_RED_P (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_SET_FATHER (struct archive_rb_node*,struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_SET_POSITION (struct archive_rb_node*,unsigned int const) ; 
 int /*<<< orphan*/  __archive_rb_tree_removal_rebalance (struct archive_rb_tree*,struct archive_rb_node*,unsigned int const) ; 

__attribute__((used)) static void
__archive_rb_tree_swap_prune_and_rebalance(struct archive_rb_tree *rbt,
    struct archive_rb_node *self, struct archive_rb_node *standin)
{
	const unsigned int standin_which = RB_POSITION(standin);
	unsigned int standin_other = standin_which ^ RB_DIR_OTHER;
	struct archive_rb_node *standin_son;
	struct archive_rb_node *standin_father = RB_FATHER(standin);
	int rebalance = RB_BLACK_P(standin);

	if (standin_father == self) {
		/*
		 * As a child of self, any children would be opposite of
		 * our parent.
		 */
		standin_son = standin->rb_nodes[standin_which];
	} else {
		/*
		 * Since we aren't a child of self, any children would be
		 * on the same side as our parent.
		 */
		standin_son = standin->rb_nodes[standin_other];
	}

	if (RB_RED_P(standin_son)) {
		/*
		 * We know we have a red child so if we flip it to black
		 * we don't have to rebalance.
		 */
		RB_MARK_BLACK(standin_son);
		rebalance = F;

		if (standin_father != self) {
			/*
			 * Change the son's parentage to point to his grandpa.
			 */
			RB_SET_FATHER(standin_son, standin_father);
			RB_SET_POSITION(standin_son, standin_which);
		}
	}

	if (standin_father == self) {
		/*
		 * If we are about to delete the standin's father, then when
		 * we call rebalance, we need to use ourselves as our father.
		 * Otherwise remember our original father.  Also, since we are
		 * our standin's father we only need to reparent the standin's
		 * brother.
		 *
		 * |    R      -->     S    |
		 * |  Q   S    -->   Q   T  |
		 * |        t  -->          |
		 *
		 * Have our son/standin adopt his brother as his new son.
		 */
		standin_father = standin;
	} else {
		/*
		 * |    R          -->    S       .  |
		 * |   / \  |   T  -->   / \  |  /   |
		 * |  ..... | S    -->  ..... | T    |
		 *
		 * Sever standin's connection to his father.
		 */
		standin_father->rb_nodes[standin_which] = standin_son;
		/*
		 * Adopt the far son.
		 */
		standin->rb_nodes[standin_other] = self->rb_nodes[standin_other];
		RB_SET_FATHER(standin->rb_nodes[standin_other], standin);
		/*
		 * Use standin_other because we need to preserve standin_which
		 * for the removal_rebalance.
		 */
		standin_other = standin_which;
	}

	/*
	 * Move the only remaining son to our standin.  If our standin is our
	 * son, this will be the only son needed to be moved.
	 */
	standin->rb_nodes[standin_other] = self->rb_nodes[standin_other];
	RB_SET_FATHER(standin->rb_nodes[standin_other], standin);

	/*
	 * Now copy the result of self to standin and then replace
	 * self with standin in the tree.
	 */
	RB_COPY_PROPERTIES(standin, self);
	RB_SET_FATHER(standin, RB_FATHER(self));
	RB_FATHER(standin)->rb_nodes[RB_POSITION(standin)] = standin;

	if (rebalance)
		__archive_rb_tree_removal_rebalance(rbt, standin_father, standin_which);
}