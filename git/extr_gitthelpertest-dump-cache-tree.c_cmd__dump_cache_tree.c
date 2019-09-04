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
struct index_state {struct cache_tree* cache_tree; } ;
struct cache_tree {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WRITE_TREE_DRY_RUN ; 
 int /*<<< orphan*/  active_cache_tree ; 
 struct cache_tree* cache_tree () ; 
 int /*<<< orphan*/  cache_tree_update (struct index_state*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  die (char*) ; 
 int dump_cache_tree (int /*<<< orphan*/ ,struct cache_tree*,char*) ; 
 scalar_t__ read_cache () ; 
 int /*<<< orphan*/  setup_git_directory () ; 
 struct index_state the_index ; 

int cmd__dump_cache_tree(int ac, const char **av)
{
	struct index_state istate;
	struct cache_tree *another = cache_tree();
	setup_git_directory();
	if (read_cache() < 0)
		die("unable to read index file");
	istate = the_index;
	istate.cache_tree = another;
	cache_tree_update(&istate, WRITE_TREE_DRY_RUN);
	return dump_cache_tree(active_cache_tree, another, "");
}