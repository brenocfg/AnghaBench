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
struct cache_tree_sub {struct cache_tree* cache_tree; } ;
struct cache_tree {int dummy; } ;

/* Variables and functions */
 struct cache_tree_sub* find_subtree (struct cache_tree*,char const*,int,int /*<<< orphan*/ ) ; 
 char* strchrnul (char const*,char) ; 

__attribute__((used)) static struct cache_tree *cache_tree_find(struct cache_tree *it, const char *path)
{
	if (!it)
		return NULL;
	while (*path) {
		const char *slash;
		struct cache_tree_sub *sub;

		slash = strchrnul(path, '/');
		/*
		 * Between path and slash is the name of the subtree
		 * to look for.
		 */
		sub = find_subtree(it, path, slash - path, 0);
		if (!sub)
			return NULL;
		it = sub->cache_tree;

		path = slash;
		while (*path == '/')
			path++;
	}
	return it;
}