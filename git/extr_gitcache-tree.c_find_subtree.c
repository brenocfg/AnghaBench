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
struct cache_tree_sub {int namelen; int /*<<< orphan*/ * cache_tree; } ;
struct cache_tree {int subtree_nr; struct cache_tree_sub** down; int /*<<< orphan*/  subtree_alloc; } ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOC_GROW (struct cache_tree_sub**,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FLEX_ALLOC_MEM (struct cache_tree_sub*,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  MOVE_ARRAY (struct cache_tree_sub**,struct cache_tree_sub**,int) ; 
 int /*<<< orphan*/  name ; 
 int subtree_pos (struct cache_tree*,char const*,int) ; 

__attribute__((used)) static struct cache_tree_sub *find_subtree(struct cache_tree *it,
					   const char *path,
					   int pathlen,
					   int create)
{
	struct cache_tree_sub *down;
	int pos = subtree_pos(it, path, pathlen);
	if (0 <= pos)
		return it->down[pos];
	if (!create)
		return NULL;

	pos = -pos-1;
	ALLOC_GROW(it->down, it->subtree_nr + 1, it->subtree_alloc);
	it->subtree_nr++;

	FLEX_ALLOC_MEM(down, name, path, pathlen);
	down->cache_tree = NULL;
	down->namelen = pathlen;

	if (pos < it->subtree_nr)
		MOVE_ARRAY(it->down + pos + 1, it->down + pos,
			   it->subtree_nr - pos - 1);
	it->down[pos] = down;
	return down;
}