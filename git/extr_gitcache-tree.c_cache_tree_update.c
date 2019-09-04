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
struct index_state {int cache_nr; int /*<<< orphan*/  cache_changed; struct cache_entry** cache; struct cache_tree* cache_tree; } ;
struct cache_tree {int dummy; } ;
struct cache_entry {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_TREE_CHANGED ; 
 int /*<<< orphan*/  trace_performance_enter () ; 
 int /*<<< orphan*/  trace_performance_leave (char*) ; 
 int update_one (struct cache_tree*,struct cache_entry**,int,char*,int /*<<< orphan*/ ,int*,int) ; 
 int verify_cache (struct cache_entry**,int,int) ; 

int cache_tree_update(struct index_state *istate, int flags)
{
	struct cache_tree *it = istate->cache_tree;
	struct cache_entry **cache = istate->cache;
	int entries = istate->cache_nr;
	int skip, i = verify_cache(cache, entries, flags);

	if (i)
		return i;
	trace_performance_enter();
	i = update_one(it, cache, entries, "", 0, &skip, flags);
	trace_performance_leave("cache_tree_update");
	if (i < 0)
		return i;
	istate->cache_changed |= CACHE_TREE_CHANGED;
	return 0;
}