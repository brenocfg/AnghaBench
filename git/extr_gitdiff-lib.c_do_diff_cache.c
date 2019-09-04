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
struct diff_options {int /*<<< orphan*/  pathspec; int /*<<< orphan*/  repo; } ;
struct rev_info {struct diff_options diffopt; int /*<<< orphan*/  prune_data; } ;
struct object_id {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  copy_pathspec (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ diff_cache (struct rev_info*,struct object_id const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  repo_init_revisions (int /*<<< orphan*/ ,struct rev_info*,int /*<<< orphan*/ *) ; 

int do_diff_cache(const struct object_id *tree_oid, struct diff_options *opt)
{
	struct rev_info revs;

	repo_init_revisions(opt->repo, &revs, NULL);
	copy_pathspec(&revs.prune_data, &opt->pathspec);
	revs.diffopt = *opt;

	if (diff_cache(&revs, tree_oid, NULL, 1))
		exit(128);
	return 0;
}