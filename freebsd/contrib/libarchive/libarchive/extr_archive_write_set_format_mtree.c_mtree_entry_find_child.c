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
struct mtree_entry {TYPE_1__* dir_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  rbtree; } ;

/* Variables and functions */
 scalar_t__ __archive_rb_tree_find_node (int /*<<< orphan*/ *,char const*) ; 

__attribute__((used)) static struct mtree_entry *
mtree_entry_find_child(struct mtree_entry *parent, const char *child_name)
{
	struct mtree_entry *np;

	if (parent == NULL)
		return (NULL);
	np = (struct mtree_entry *)__archive_rb_tree_find_node(
	    &(parent->dir_info->rbtree), child_name);
	return (np);
}