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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ATTR_CHECK_NO_SYSTEM ; 
 int /*<<< orphan*/  GIT_ATTR_IS_UNSPECIFIED (char const*) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  git_attr_get (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  git_repository_is_bare (int /*<<< orphan*/ *) ; 

void test_attr_flags__bare(void)
{
	git_repository *repo = cl_git_sandbox_init("testrepo.git");
	const char *value;

	cl_assert(git_repository_is_bare(repo));

	cl_git_pass(git_attr_get(
		&value, repo, GIT_ATTR_CHECK_NO_SYSTEM, "README.md", "diff"));
	cl_assert(GIT_ATTR_IS_UNSPECIFIED(value));
}