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
struct archive_rb_node {struct archive_rb_node** rb_nodes; struct archive_rb_node* rb_right; struct archive_rb_node* rb_left; } ;
typedef  int (* archive_rbto_compare_nodes_fn ) (struct archive_rb_node*,struct archive_rb_node*) ;
struct TYPE_2__ {int (* rbto_compare_nodes ) (struct archive_rb_node*,struct archive_rb_node*) ;} ;

/* Variables and functions */
 int F ; 
 unsigned int RB_DIR_LEFT ; 
 int /*<<< orphan*/  RB_MARK_BLACK (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_MARK_RED (struct archive_rb_node*) ; 
 int RB_RED_P (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_SENTINEL_P (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_SET_FATHER (struct archive_rb_node*,struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_SET_POSITION (struct archive_rb_node*,unsigned int) ; 
 int T ; 
 int /*<<< orphan*/  __archive_rb_tree_insert_rebalance (struct archive_rb_tree*,struct archive_rb_node*) ; 
 int stub1 (struct archive_rb_node*,struct archive_rb_node*) ; 

int
__archive_rb_tree_insert_node(struct archive_rb_tree *rbt,
    struct archive_rb_node *self)
{
	archive_rbto_compare_nodes_fn compare_nodes = rbt->rbt_ops->rbto_compare_nodes;
	struct archive_rb_node *parent, *tmp;
	unsigned int position;
	int rebalance;

	tmp = rbt->rbt_root;
	/*
	 * This is a hack.  Because rbt->rbt_root is just a
	 * struct archive_rb_node *, just like rb_node->rb_nodes[RB_DIR_LEFT],
	 * we can use this fact to avoid a lot of tests for root and know
	 * that even at root, updating
	 * RB_FATHER(rb_node)->rb_nodes[RB_POSITION(rb_node)] will
	 * update rbt->rbt_root.
	 */
	parent = (struct archive_rb_node *)(void *)&rbt->rbt_root;
	position = RB_DIR_LEFT;

	/*
	 * Find out where to place this new leaf.
	 */
	while (!RB_SENTINEL_P(tmp)) {
		const signed int diff = (*compare_nodes)(tmp, self);
		if (diff == 0) {
			/*
			 * Node already exists; don't insert.
			 */
			return F;
		}
		parent = tmp;
		position = (diff > 0);
		tmp = parent->rb_nodes[position];
	}

	/*
	 * Initialize the node and insert as a leaf into the tree.
	 */
	RB_SET_FATHER(self, parent);
	RB_SET_POSITION(self, position);
	if (parent == (struct archive_rb_node *)(void *)&rbt->rbt_root) {
		RB_MARK_BLACK(self);		/* root is always black */
		rebalance = F;
	} else {
		/*
		 * All new nodes are colored red.  We only need to rebalance
		 * if our parent is also red.
		 */
		RB_MARK_RED(self);
		rebalance = RB_RED_P(parent);
	}
	self->rb_left = parent->rb_nodes[position];
	self->rb_right = parent->rb_nodes[position];
	parent->rb_nodes[position] = self;

	/*
	 * Rebalance tree after insertion
	 */
	if (rebalance)
		__archive_rb_tree_insert_rebalance(rbt, self);

	return T;
}