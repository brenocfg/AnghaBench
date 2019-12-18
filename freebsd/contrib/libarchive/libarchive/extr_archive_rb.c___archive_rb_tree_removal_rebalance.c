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
struct archive_rb_node {struct archive_rb_node** rb_nodes; struct archive_rb_node* rb_right; struct archive_rb_node* rb_left; } ;

/* Variables and functions */
 scalar_t__ RB_BLACK_P (struct archive_rb_node*) ; 
 unsigned int RB_DIR_OTHER ; 
 struct archive_rb_node* RB_FATHER (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_MARK_BLACK (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_MARK_RED (struct archive_rb_node*) ; 
 unsigned int RB_POSITION (struct archive_rb_node*) ; 
 scalar_t__ RB_RED_P (struct archive_rb_node*) ; 
 scalar_t__ RB_ROOT_P (struct archive_rb_tree*,struct archive_rb_node*) ; 
 int /*<<< orphan*/  __archive_rb_tree_reparent_nodes (struct archive_rb_node*,unsigned int) ; 

__attribute__((used)) static void
__archive_rb_tree_removal_rebalance(struct archive_rb_tree *rbt,
    struct archive_rb_node *parent, unsigned int which)
{

	while (RB_BLACK_P(parent->rb_nodes[which])) {
		unsigned int other = which ^ RB_DIR_OTHER;
		struct archive_rb_node *brother = parent->rb_nodes[other];

		if (brother == NULL)
			return;/* The tree may be broken. */
		/*
		 * For cases 1, 2a, and 2b, our brother's children must
		 * be black and our father must be black
		 */
		if (RB_BLACK_P(parent)
		    && RB_BLACK_P(brother->rb_left)
		    && RB_BLACK_P(brother->rb_right)) {
			if (RB_RED_P(brother)) {
				/*
				 * Case 1: Our brother is red, swap its
				 * position (and colors) with our parent. 
				 * This should now be case 2b (unless C or E
				 * has a red child which is case 3; thus no
				 * explicit branch to case 2b).
				 *
				 *    B         ->        D
				 *  A     d     ->    b     E
				 *      C   E   ->  A   C
				 */
				__archive_rb_tree_reparent_nodes(parent, other);
				brother = parent->rb_nodes[other];
				if (brother == NULL)
					return;/* The tree may be broken. */
			} else {
				/*
				 * Both our parent and brother are black.
				 * Change our brother to red, advance up rank
				 * and go through the loop again.
				 *
				 *    B         ->   *B
				 * *A     D     ->  A     d
				 *      C   E   ->      C   E
				 */
				RB_MARK_RED(brother);
				if (RB_ROOT_P(rbt, parent))
					return;	/* root == parent == black */
				which = RB_POSITION(parent);
				parent = RB_FATHER(parent);
				continue;
			}
		}
		/*
		 * Avoid an else here so that case 2a above can hit either
		 * case 2b, 3, or 4.
		 */
		if (RB_RED_P(parent)
		    && RB_BLACK_P(brother)
		    && RB_BLACK_P(brother->rb_left)
		    && RB_BLACK_P(brother->rb_right)) {
			/*
			 * We are black, our father is red, our brother and
			 * both nephews are black.  Simply invert/exchange the
			 * colors of our father and brother (to black and red
			 * respectively).
			 *
			 *	|    f        -->    F        |
			 *	|  *     B    -->  *     b    |
			 *	|      N   N  -->      N   N  |
			 */
			RB_MARK_BLACK(parent);
			RB_MARK_RED(brother);
			break;		/* We're done! */
		} else {
			/*
			 * Our brother must be black and have at least one
			 * red child (it may have two).
			 */
			if (RB_BLACK_P(brother->rb_nodes[other])) {
				/*
				 * Case 3: our brother is black, our near
				 * nephew is red, and our far nephew is black.
				 * Swap our brother with our near nephew.  
				 * This result in a tree that matches case 4.
				 * (Our father could be red or black).
				 *
				 *	|    F      -->    F      |
				 *	|  x     B  -->  x   B    |
				 *	|      n    -->        n  |
				 */
				__archive_rb_tree_reparent_nodes(brother, which);
				brother = parent->rb_nodes[other];
			}
			/*
			 * Case 4: our brother is black and our far nephew
			 * is red.  Swap our father and brother locations and
			 * change our far nephew to black.  (these can be
			 * done in either order so we change the color first).
			 * The result is a valid red-black tree and is a
			 * terminal case.  (again we don't care about the
			 * father's color)
			 *
			 * If the father is red, we will get a red-black-black
			 * tree:
			 *	|  f      ->  f      -->    b    |
			 *	|    B    ->    B    -->  F   N  |
			 *	|      n  ->      N  -->         |
			 *
			 * If the father is black, we will get an all black
			 * tree:
			 *	|  F      ->  F      -->    B    |
			 *	|    B    ->    B    -->  F   N  |
			 *	|      n  ->      N  -->         |
			 *
			 * If we had two red nephews, then after the swap,
			 * our former father would have a red grandson. 
			 */
			if (brother->rb_nodes[other] == NULL)
				return;/* The tree may be broken. */
			RB_MARK_BLACK(brother->rb_nodes[other]);
			__archive_rb_tree_reparent_nodes(parent, other);
			break;		/* We're done! */
		}
	}
}