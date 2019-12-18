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
struct unpack_trees_options {TYPE_1__* src_index; int /*<<< orphan*/  merge; } ;
struct traverse_info {struct unpack_trees_options* data; } ;
struct name_entry {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  cache_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  are_same_oid (struct name_entry*,struct name_entry*) ; 
 int cache_tree_matches_traversal (int /*<<< orphan*/ ,struct name_entry*,struct traverse_info*) ; 

__attribute__((used)) static int all_trees_same_as_cache_tree(int n, unsigned long dirmask,
					struct name_entry *names,
					struct traverse_info *info)
{
	struct unpack_trees_options *o = info->data;
	int i;

	if (!o->merge || dirmask != ((1 << n) - 1))
		return 0;

	for (i = 1; i < n; i++)
		if (!are_same_oid(names, names + i))
			return 0;

	return cache_tree_matches_traversal(o->src_index->cache_tree, names, info);
}