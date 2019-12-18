#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_13__ {int /*<<< orphan*/  inmemory; } ;
typedef  TYPE_1__ git_rebase_options ;
struct TYPE_14__ {int inmemory; int /*<<< orphan*/  type; int /*<<< orphan*/ * repo; } ;
typedef  TYPE_2__ git_rebase ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR ; 
 int /*<<< orphan*/  GIT_REBASE_TYPE_MERGE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_rebase_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int git_repository__ensure_not_bare (int /*<<< orphan*/ *,char*) ; 
 int git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ rebase_alloc (TYPE_2__**,TYPE_1__ const*) ; 
 int rebase_check_versions (TYPE_1__ const*) ; 
 int /*<<< orphan*/  rebase_cleanup (TYPE_2__*) ; 
 int rebase_ensure_not_dirty (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int rebase_ensure_not_in_progress (int /*<<< orphan*/ *) ; 
 int rebase_init_inmemory (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int rebase_init_merge (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 int rebase_init_operations (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 

int git_rebase_init(
	git_rebase **out,
	git_repository *repo,
	const git_annotated_commit *branch,
	const git_annotated_commit *upstream,
	const git_annotated_commit *onto,
	const git_rebase_options *given_opts)
{
	git_rebase *rebase = NULL;
	git_annotated_commit *head_branch = NULL;
	git_reference *head_ref = NULL;
	bool inmemory = (given_opts && given_opts->inmemory);
	int error;

	assert(repo && (upstream || onto));

	*out = NULL;

	if (!onto)
		onto = upstream;

	if ((error = rebase_check_versions(given_opts)) < 0)
		goto done;

	if (!inmemory) {
		if ((error = git_repository__ensure_not_bare(repo, "rebase")) < 0 ||
			(error = rebase_ensure_not_in_progress(repo)) < 0 ||
			(error = rebase_ensure_not_dirty(repo, true, true, GIT_ERROR)) < 0)
			goto done;
	}

	if (!branch) {
		if ((error = git_repository_head(&head_ref, repo)) < 0 ||
			(error = git_annotated_commit_from_ref(&head_branch, repo, head_ref)) < 0)
			goto done;

		branch = head_branch;
	}

	if (rebase_alloc(&rebase, given_opts) < 0)
		return -1;

	rebase->repo = repo;
	rebase->inmemory = inmemory;
	rebase->type = GIT_REBASE_TYPE_MERGE;

	if ((error = rebase_init_operations(rebase, repo, branch, upstream, onto)) < 0)
		goto done;

	if (inmemory)
		error = rebase_init_inmemory(rebase, repo, branch, upstream, onto);
	else
		error = rebase_init_merge(rebase, repo, branch ,upstream, onto);

	if (error == 0)
		*out = rebase;

done:
	git_reference_free(head_ref);
	git_annotated_commit_free(head_branch);

	if (error < 0) {
		rebase_cleanup(rebase);
		git_rebase_free(rebase);
	}

	return error;
}