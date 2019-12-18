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
struct merge_options {int /*<<< orphan*/  repo; } ;
typedef  int /*<<< orphan*/  match_all ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct pathspec*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_tree_recursive (int /*<<< orphan*/ ,struct tree*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pathspec*,int /*<<< orphan*/ ,struct merge_options*) ; 
 int /*<<< orphan*/  save_files_dirs ; 

__attribute__((used)) static void get_files_dirs(struct merge_options *opt, struct tree *tree)
{
	struct pathspec match_all;
	memset(&match_all, 0, sizeof(match_all));
	read_tree_recursive(opt->repo, tree, "", 0, 0,
			    &match_all, save_files_dirs, opt);
}