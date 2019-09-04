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
struct index_state {int /*<<< orphan*/  cache_changed; int /*<<< orphan*/  cache_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  CACHE_TREE_CHANGED ; 
 scalar_t__ do_invalidate_path (int /*<<< orphan*/ ,char const*) ; 

void cache_tree_invalidate_path(struct index_state *istate, const char *path)
{
	if (do_invalidate_path(istate->cache_tree, path))
		istate->cache_changed |= CACHE_TREE_CHANGED;
}