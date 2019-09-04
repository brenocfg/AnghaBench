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
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  git_strmap_clear (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_strmap_foreach_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_tree_entry_free (int /*<<< orphan*/ *) ; 

void git_treebuilder_clear(git_treebuilder *bld)
{
	git_tree_entry *e;

	assert(bld);

	git_strmap_foreach_value(bld->map, e, git_tree_entry_free(e));
	git_strmap_clear(bld->map);
}