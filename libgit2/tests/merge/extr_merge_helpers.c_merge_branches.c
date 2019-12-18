#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_merge_options ;
struct TYPE_6__ {int /*<<< orphan*/  checkout_strategy; } ;
typedef  TYPE_1__ git_checkout_options ;
typedef  int /*<<< orphan*/  git_annotated_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CHECKOUT_FORCE ; 
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_checkout_head (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_merge (int /*<<< orphan*/ *,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*,char const*,int,int /*<<< orphan*/ *) ; 

int merge_branches(git_repository *repo,
	const char *ours_branch, const char *theirs_branch,
	git_merge_options *merge_opts, git_checkout_options *checkout_opts)
{
	git_reference *head_ref, *theirs_ref;
	git_annotated_commit *theirs_head;
	git_checkout_options head_checkout_opts = GIT_CHECKOUT_OPTIONS_INIT;

	head_checkout_opts.checkout_strategy = GIT_CHECKOUT_FORCE;

	cl_git_pass(git_reference_symbolic_create(&head_ref, repo, "HEAD", ours_branch, 1, NULL));
	cl_git_pass(git_checkout_head(repo, &head_checkout_opts));

	cl_git_pass(git_reference_lookup(&theirs_ref, repo, theirs_branch));
	cl_git_pass(git_annotated_commit_from_ref(&theirs_head, repo, theirs_ref));

	cl_git_pass(git_merge(repo, (const git_annotated_commit **)&theirs_head, 1, merge_opts, checkout_opts));

	git_reference_free(head_ref);
	git_reference_free(theirs_ref);
	git_annotated_commit_free(theirs_head);

	return 0;
}