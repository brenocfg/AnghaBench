#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_annotated_commit ;
struct TYPE_2__ {int /*<<< orphan*/  worktree; } ;

/* Variables and functions */
 int /*<<< orphan*/  CONFLICT_BRANCH ; 
 int /*<<< orphan*/  GIT_MERGE_HEAD_FILE ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_1__ fixture ; 
 int /*<<< orphan*/  git_annotated_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_annotated_commit_from_ref (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_merge (int /*<<< orphan*/ ,int /*<<< orphan*/  const**,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_worktree_merge__merge_head(void)
{
	git_reference *theirs_ref, *ref;
	git_annotated_commit *theirs;

	cl_git_pass(git_reference_lookup(&theirs_ref, fixture.worktree, CONFLICT_BRANCH));
	cl_git_pass(git_annotated_commit_from_ref(&theirs, fixture.worktree, theirs_ref));
	cl_git_pass(git_merge(fixture.worktree, (const git_annotated_commit **)&theirs, 1, NULL, NULL));

	cl_git_pass(git_reference_lookup(&ref, fixture.worktree, GIT_MERGE_HEAD_FILE));

	git_reference_free(ref);
	git_reference_free(theirs_ref);
	git_annotated_commit_free(theirs);
}