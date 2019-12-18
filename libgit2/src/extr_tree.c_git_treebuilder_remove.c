#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  map; } ;
typedef  TYPE_1__ git_treebuilder ;
typedef  int /*<<< orphan*/  git_tree_entry ;

/* Variables and functions */
 int /*<<< orphan*/  git_strmap_delete (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 
 int tree_error (char*,char const*) ; 
 int /*<<< orphan*/ * treebuilder_get (TYPE_1__*,char const*) ; 

int git_treebuilder_remove(git_treebuilder *bld, const char *filename)
{
	git_tree_entry *entry = treebuilder_get(bld, filename);

	if (entry == NULL)
		return tree_error("failed to remove entry: file isn't in the tree", filename);

	git_strmap_delete(bld->map, filename);
	git_tree_entry_free(entry);

	return 0;
}