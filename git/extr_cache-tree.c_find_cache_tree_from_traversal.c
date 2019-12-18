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
struct traverse_info {int /*<<< orphan*/  name; struct traverse_info* prev; } ;
struct cache_tree {int dummy; } ;

/* Variables and functions */
 struct cache_tree* cache_tree_find (struct cache_tree*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cache_tree *find_cache_tree_from_traversal(struct cache_tree *root,
							 struct traverse_info *info)
{
	struct cache_tree *our_parent;

	if (!info->prev)
		return root;
	our_parent = find_cache_tree_from_traversal(root, info->prev);
	return cache_tree_find(our_parent, info->name);
}