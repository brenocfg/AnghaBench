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
typedef  int /*<<< orphan*/  git_tree_cache ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_tree_cache_write(git_buf *out, git_tree_cache *tree)
{
	write_tree(out, tree);

	return git_buf_oom(out) ? -1 : 0;
}