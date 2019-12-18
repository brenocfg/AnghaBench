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
typedef  int /*<<< orphan*/  git_index ;

/* Variables and functions */
 int GIT_INDEX_CAPABILITY_IGNORE_CASE ; 
 int /*<<< orphan*/  GIT_STATUS_IGNORED ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int git_index_caps (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_index_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_index (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_file (unsigned int*,int /*<<< orphan*/ ,char*) ; 

void test_ignore_status__ignore_pattern_ignorecase(void)
{
	unsigned int flags;
	bool ignore_case;
	git_index *index;

	g_repo = cl_git_sandbox_init("empty_standard_repo");
	cl_git_rewritefile("empty_standard_repo/.gitignore", "a.txt\n");

	cl_git_mkfile("empty_standard_repo/A.txt", "Differs in case");

	cl_git_pass(git_repository_index(&index, g_repo));
	ignore_case = (git_index_caps(index) & GIT_INDEX_CAPABILITY_IGNORE_CASE) != 0;
	git_index_free(index);

	cl_git_pass(git_status_file(&flags, g_repo, "A.txt"));
	cl_assert(flags == ignore_case ? GIT_STATUS_IGNORED : GIT_STATUS_WT_NEW);
}