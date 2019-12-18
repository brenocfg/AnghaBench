#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cnt; struct isoent** last; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt; struct isoent** last; } ;
struct isoent {struct isoent* parent; TYPE_2__ subdirs; struct isoent* drnext; scalar_t__ dir; TYPE_1__ children; struct isoent* chnext; int /*<<< orphan*/  rbtree; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_rb_tree_insert_node (int /*<<< orphan*/ *,struct archive_rb_node*) ; 

__attribute__((used)) static int
isoent_add_child_tail(struct isoent *parent, struct isoent *child)
{

	if (!__archive_rb_tree_insert_node(
	    &(parent->rbtree), (struct archive_rb_node *)child))
		return (0);
	child->chnext = NULL;
	*parent->children.last = child;
	parent->children.last = &(child->chnext);
	parent->children.cnt++;
	child->parent = parent;

	/* Add a child to a sub-directory chain */
	child->drnext = NULL;
	if (child->dir) {
		*parent->subdirs.last = child;
		parent->subdirs.last = &(child->drnext);
		parent->subdirs.cnt++;
		child->parent = parent;
	}
	return (1);
}