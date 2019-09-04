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
typedef  int /*<<< orphan*/  git_reference ;

/* Variables and functions */
 int /*<<< orphan*/  NON_EXISTING_HEAD ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_symbolic_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_head_detached (int /*<<< orphan*/ ) ; 
 int git_repository_head_unborn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_head_unborn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 

void test_repo_head__unborn_head(void)
{
	git_reference *ref;

	cl_git_pass(git_repository_head_detached(repo));

	make_head_unborn(repo, NON_EXISTING_HEAD);

	cl_assert(git_repository_head_unborn(repo) == 1);


	/* take the repo back to it's original state */
	cl_git_pass(git_reference_symbolic_create(&ref, repo, "HEAD", "refs/heads/master", 1, NULL));
	cl_assert(git_repository_head_unborn(repo) == 0);

	git_reference_free(ref);
}