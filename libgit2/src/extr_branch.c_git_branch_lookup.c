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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int git_branch_t ;

/* Variables and functions */
#define  GIT_BRANCH_ALL 130 
#define  GIT_BRANCH_LOCAL 129 
#define  GIT_BRANCH_REMOTE 128 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  assert (int) ; 
 int retrieve_branch_reference (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*,int) ; 

int git_branch_lookup(
	git_reference **ref_out,
	git_repository *repo,
	const char *branch_name,
	git_branch_t branch_type)
{
	int error = -1;
	assert(ref_out && repo && branch_name);

	switch (branch_type) {
	case GIT_BRANCH_LOCAL:
	case GIT_BRANCH_REMOTE:
		error = retrieve_branch_reference(ref_out, repo, branch_name, branch_type == GIT_BRANCH_REMOTE);
		break;
	case GIT_BRANCH_ALL:
		error = retrieve_branch_reference(ref_out, repo, branch_name, false);
		if (error == GIT_ENOTFOUND)
			error = retrieve_branch_reference(ref_out, repo, branch_name, true);
		break;
	default:
		assert(false);
	}
	return error;
}