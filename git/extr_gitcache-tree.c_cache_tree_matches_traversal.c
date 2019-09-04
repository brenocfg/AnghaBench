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
struct traverse_info {int dummy; } ;
struct name_entry {int /*<<< orphan*/  oid; int /*<<< orphan*/  path; } ;
struct cache_tree {scalar_t__ entry_count; int /*<<< orphan*/  oid; } ;

/* Variables and functions */
 struct cache_tree* cache_tree_find (struct cache_tree*,int /*<<< orphan*/ ) ; 
 struct cache_tree* find_cache_tree_from_traversal (struct cache_tree*,struct traverse_info*) ; 
 scalar_t__ oideq (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int cache_tree_matches_traversal(struct cache_tree *root,
				 struct name_entry *ent,
				 struct traverse_info *info)
{
	struct cache_tree *it;

	it = find_cache_tree_from_traversal(root, info);
	it = cache_tree_find(it, ent->path);
	if (it && it->entry_count > 0 && oideq(&ent->oid, &it->oid))
		return it->entry_count;
	return 0;
}