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
struct archive_rb_node {struct archive_rb_node** rb_nodes; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_COPY_PROPERTIES (struct archive_rb_node*,struct archive_rb_node*) ; 
 struct archive_rb_node* RB_FATHER (struct archive_rb_node*) ; 
 size_t RB_POSITION (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_SET_FATHER (struct archive_rb_node*,struct archive_rb_node*) ; 

__attribute__((used)) static void
__archive_rb_tree_prune_blackred_branch(
    struct archive_rb_node *self, unsigned int which)
{
	struct archive_rb_node *father = RB_FATHER(self);
	struct archive_rb_node *son = self->rb_nodes[which];

	/*
	 * Remove ourselves from the tree and give our former child our
	 * properties (position, color, root).
	 */
	RB_COPY_PROPERTIES(son, self);
	father->rb_nodes[RB_POSITION(son)] = son;
	RB_SET_FATHER(son, father);
}