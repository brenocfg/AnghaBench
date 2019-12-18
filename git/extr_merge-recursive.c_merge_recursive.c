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
struct merge_options {int /*<<< orphan*/  repo; int /*<<< orphan*/ * ancestor; } ;
struct commit_list {int dummy; } ;
struct commit {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  merge_finalize (struct merge_options*) ; 
 int merge_recursive_internal (struct merge_options*,struct commit*,struct commit*,struct commit_list*,struct commit**) ; 
 scalar_t__ merge_start (struct merge_options*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo_get_commit_tree (int /*<<< orphan*/ ,struct commit*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

int merge_recursive(struct merge_options *opt,
		    struct commit *h1,
		    struct commit *h2,
		    struct commit_list *merge_bases,
		    struct commit **result)
{
	int clean;

	assert(opt->ancestor == NULL ||
	       !strcmp(opt->ancestor, "constructed merge base"));

	if (merge_start(opt, repo_get_commit_tree(opt->repo, h1)))
		return -1;
	clean = merge_recursive_internal(opt, h1, h2, merge_bases, result);
	merge_finalize(opt);

	return clean;
}