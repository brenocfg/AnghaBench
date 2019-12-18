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
struct TYPE_4__ {int /*<<< orphan*/  cnt; struct isoent* first; struct isoent** last; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt; struct isoent* first; struct isoent** last; } ;
struct isoent {struct isoent* drnext; struct isoent* parent; TYPE_2__ subdirs; scalar_t__ dir; TYPE_1__ children; struct isoent* chnext; int /*<<< orphan*/  rbtree; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_rb_tree_insert_node (int /*<<< orphan*/ *,struct archive_rb_node*) ; 

__attribute__((used)) static int
isoent_add_child_head(struct isoent *parent, struct isoent *child)
{

	if (!__archive_rb_tree_insert_node(
	    &(parent->rbtree), (struct archive_rb_node *)child))
		return (0);
	if ((child->chnext = parent->children.first) == NULL)
		parent->children.last = &(child->chnext);
	parent->children.first = child;
	parent->children.cnt++;
	child->parent = parent;

	/* Add a child to a sub-directory chain */
	if (child->dir) {
		if ((child->drnext = parent->subdirs.first) == NULL)
			parent->subdirs.last = &(child->drnext);
		parent->subdirs.first = child;
		parent->subdirs.cnt++;
		child->parent = parent;
	} else
		child->drnext = NULL;
	return (1);
}