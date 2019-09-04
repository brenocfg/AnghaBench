#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__** contents; int /*<<< orphan*/  length; } ;
typedef  TYPE_1__ git_vector ;
struct TYPE_11__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ git_reference ;
struct TYPE_12__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  repo; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (TYPE_2__**) ; 
 int /*<<< orphan*/  GIT_HEAD_FILE ; 
 TYPE_1__ GIT_VECTOR_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 TYPE_7__ fixture ; 
 int /*<<< orphan*/  git_reference_free (TYPE_2__*) ; 
 int /*<<< orphan*/  git_reference_lookup (TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_foreach_head (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  git_vector_free (TYPE_1__*) ; 
 int /*<<< orphan*/  read_head_ref ; 

void test_worktree_worktree__foreach_head_gives_same_results_in_wt_and_repo(void)
{
	git_vector repo_refs = GIT_VECTOR_INIT, worktree_refs = GIT_VECTOR_INIT;
	git_reference *heads[2];
	size_t i;

	cl_git_pass(git_reference_lookup(&heads[0], fixture.repo, GIT_HEAD_FILE));
	cl_git_pass(git_reference_lookup(&heads[1], fixture.worktree, GIT_HEAD_FILE));

	cl_git_pass(git_repository_foreach_head(fixture.repo, read_head_ref, 0, &repo_refs));
	cl_git_pass(git_repository_foreach_head(fixture.worktree, read_head_ref, 0, &worktree_refs));

	cl_assert_equal_i(repo_refs.length, ARRAY_SIZE(heads));
	cl_assert_equal_i(worktree_refs.length, ARRAY_SIZE(heads));

	for (i = 0; i < ARRAY_SIZE(heads); i++) {
		cl_assert_equal_s(heads[i]->name, ((git_reference *) repo_refs.contents[i])->name);
		cl_assert_equal_s(heads[i]->name, ((git_reference *) repo_refs.contents[i])->name);
		cl_assert_equal_s(heads[i]->name, ((git_reference *) worktree_refs.contents[i])->name);

		git_reference_free(heads[i]);
		git_reference_free(repo_refs.contents[i]);
		git_reference_free(worktree_refs.contents[i]);
	}

	git_vector_free(&repo_refs);
	git_vector_free(&worktree_refs);
}