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
struct archive_rb_node {struct archive_rb_node** rb_nodes; } ;

/* Variables and functions */
 unsigned int const RB_DIR_OTHER ; 
 struct archive_rb_node* RB_FATHER (struct archive_rb_node*) ; 
 scalar_t__ RB_POSITION (struct archive_rb_node*) ; 
 int /*<<< orphan*/  RB_ROOT_P (struct archive_rb_tree*,struct archive_rb_node*) ; 
 scalar_t__ RB_SENTINEL_P (struct archive_rb_node*) ; 

struct archive_rb_node *
__archive_rb_tree_iterate(struct archive_rb_tree *rbt,
    struct archive_rb_node *self, const unsigned int direction)
{
	const unsigned int other = direction ^ RB_DIR_OTHER;

	if (self == NULL) {
		self = rbt->rbt_root;
		if (RB_SENTINEL_P(self))
			return NULL;
		while (!RB_SENTINEL_P(self->rb_nodes[direction]))
			self = self->rb_nodes[direction];
		return self;
	}
	/*
	 * We can't go any further in this direction.  We proceed up in the
	 * opposite direction until our parent is in direction we want to go.
	 */
	if (RB_SENTINEL_P(self->rb_nodes[direction])) {
		while (!RB_ROOT_P(rbt, self)) {
			if (other == (unsigned int)RB_POSITION(self))
				return RB_FATHER(self);
			self = RB_FATHER(self);
		}
		return NULL;
	}

	/*
	 * Advance down one in current direction and go down as far as possible
	 * in the opposite direction.
	 */
	self = self->rb_nodes[direction];
	while (!RB_SENTINEL_P(self->rb_nodes[other]))
		self = self->rb_nodes[other];
	return self;
}