#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_revwalk ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_rebase_operation ;
struct TYPE_4__ {int /*<<< orphan*/  repo; } ;
typedef  TYPE_1__ git_rebase ;
typedef  int /*<<< orphan*/  git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_CHECK_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GIT_REBASE_OPERATION_PICK ; 
 int /*<<< orphan*/  GIT_SORT_REVERSE ; 
 int /*<<< orphan*/  git_annotated_commit_id (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_commit_parentcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_revwalk_free (int /*<<< orphan*/ *) ; 
 int git_revwalk_hide (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_revwalk_new (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int git_revwalk_next (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int git_revwalk_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_revwalk_sorting (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * rebase_operation_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int rebase_init_operations(
	git_rebase *rebase,
	git_repository *repo,
	const git_annotated_commit *branch,
	const git_annotated_commit *upstream,
	const git_annotated_commit *onto)
{
	git_revwalk *revwalk = NULL;
	git_commit *commit;
	git_oid id;
	bool merge;
	git_rebase_operation *operation;
	int error;

	if (!upstream)
		upstream = onto;

	if ((error = git_revwalk_new(&revwalk, rebase->repo)) < 0 ||
		(error = git_revwalk_push(revwalk, git_annotated_commit_id(branch))) < 0 ||
		(error = git_revwalk_hide(revwalk, git_annotated_commit_id(upstream))) < 0)
		goto done;

	git_revwalk_sorting(revwalk, GIT_SORT_REVERSE);

	while ((error = git_revwalk_next(&id, revwalk)) == 0) {
		if ((error = git_commit_lookup(&commit, repo, &id)) < 0)
			goto done;

		merge = (git_commit_parentcount(commit) > 1);
		git_commit_free(commit);

		if (merge)
			continue;

		operation = rebase_operation_alloc(rebase, GIT_REBASE_OPERATION_PICK, &id, NULL);
		GIT_ERROR_CHECK_ALLOC(operation);
	}

	error = 0;

done:
	git_revwalk_free(revwalk);
	return error;
}