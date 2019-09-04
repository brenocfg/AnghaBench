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
struct unpack_trees_options {int /*<<< orphan*/  src_index; } ;
struct cache_entry {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  cache_tree_invalidate_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untracked_cache_invalidate_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void invalidate_ce_path(const struct cache_entry *ce,
			       struct unpack_trees_options *o)
{
	if (!ce)
		return;
	cache_tree_invalidate_path(o->src_index, ce->name);
	untracked_cache_invalidate_path(o->src_index, ce->name, 1);
}