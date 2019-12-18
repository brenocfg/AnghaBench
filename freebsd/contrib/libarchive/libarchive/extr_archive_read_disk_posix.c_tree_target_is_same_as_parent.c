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
struct tree_entry {scalar_t__ dev; scalar_t__ ino; struct tree_entry* parent; } ;
struct tree {TYPE_1__* current; } ;
struct stat {scalar_t__ st_ino; scalar_t__ st_dev; } ;
typedef  scalar_t__ int64_t ;
struct TYPE_2__ {struct tree_entry* parent; } ;

/* Variables and functions */

__attribute__((used)) static int
tree_target_is_same_as_parent(struct tree *t, const struct stat *st)
{
	struct tree_entry *te;

	for (te = t->current->parent; te != NULL; te = te->parent) {
		if (te->dev == (int64_t)st->st_dev &&
		    te->ino == (int64_t)st->st_ino)
			return (1);
	}
	return (0);
}