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
struct TYPE_4__ {int /*<<< orphan*/  cnt; struct isoent** last; struct isoent* first; } ;
struct TYPE_3__ {int /*<<< orphan*/  cnt; struct isoent** last; struct isoent* first; } ;
struct isoent {int /*<<< orphan*/  rbtree; TYPE_2__ subdirs; struct isoent* drnext; scalar_t__ dir; TYPE_1__ children; struct isoent* chnext; } ;
struct archive_rb_node {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __archive_rb_tree_remove_node (int /*<<< orphan*/ *,struct archive_rb_node*) ; 

__attribute__((used)) static void
isoent_remove_child(struct isoent *parent, struct isoent *child)
{
	struct isoent *ent;

	/* Remove a child entry from children chain. */
	ent = parent->children.first;
	while (ent->chnext != child)
		ent = ent->chnext;
	if ((ent->chnext = ent->chnext->chnext) == NULL)
		parent->children.last = &(ent->chnext);
	parent->children.cnt--;

	if (child->dir) {
		/* Remove a child entry from sub-directory chain. */
		ent = parent->subdirs.first;
		while (ent->drnext != child)
			ent = ent->drnext;
		if ((ent->drnext = ent->drnext->drnext) == NULL)
			parent->subdirs.last = &(ent->drnext);
		parent->subdirs.cnt--;
	}

	__archive_rb_tree_remove_node(&(parent->rbtree),
	    (struct archive_rb_node *)child);
}