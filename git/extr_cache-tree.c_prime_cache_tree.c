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
struct tree {int dummy; } ;
struct repository {int dummy; } ;
struct index_state {int /*<<< orphan*/  cache_changed; int /*<<< orphan*/  cache_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_TREE_CHANGED ; 
 int /*<<< orphan*/  cache_tree () ; 
 int /*<<< orphan*/  cache_tree_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prime_cache_tree_rec (struct repository*,int /*<<< orphan*/ ,struct tree*) ; 

void prime_cache_tree(struct repository *r,
		      struct index_state *istate,
		      struct tree *tree)
{
	cache_tree_free(&istate->cache_tree);
	istate->cache_tree = cache_tree();
	prime_cache_tree_rec(r, istate->cache_tree, tree);
	istate->cache_changed |= CACHE_TREE_CHANGED;
}