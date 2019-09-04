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
struct pathspec {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  read_tree_recursive (int /*<<< orphan*/ ,struct tree*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pathspec const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  the_repository ; 
 int /*<<< orphan*/  update_some ; 

__attribute__((used)) static int read_tree_some(struct tree *tree, const struct pathspec *pathspec)
{
	read_tree_recursive(the_repository, tree, "", 0, 0,
			    pathspec, update_some, NULL);

	/* update the index with the given tree's info
	 * for all args, expanding wildcards, and exit
	 * with any non-zero return code.
	 */
	return 0;
}