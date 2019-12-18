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
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit_list_node ;

/* Variables and functions */
 scalar_t__ ahead_behind (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t*,size_t*) ; 
 int /*<<< orphan*/ * git_revwalk__commit_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ mark_parents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int git_graph_ahead_behind(size_t *ahead, size_t *behind, git_repository *repo,
	const git_oid *local, const git_oid *upstream)
{
	git_revwalk *walk;
	git_commit_list_node *commit_u, *commit_l;

	if (git_revwalk_new(&walk, repo) < 0)
		return -1;

	commit_u = git_revwalk__commit_lookup(walk, upstream);
	if (commit_u == NULL)
		goto on_error;

	commit_l = git_revwalk__commit_lookup(walk, local);
	if (commit_l == NULL)
		goto on_error;

	if (mark_parents(walk, commit_l, commit_u) < 0)
		goto on_error;
	if (ahead_behind(commit_l, commit_u, ahead, behind) < 0)
		goto on_error;

	git_revwalk_free(walk);

	return 0;

on_error:
	git_revwalk_free(walk);
	return -1;
}