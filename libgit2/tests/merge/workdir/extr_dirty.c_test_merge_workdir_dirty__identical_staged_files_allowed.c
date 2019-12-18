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

/* Variables and functions */
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_index_write (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_branch () ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  repo_index ; 
 char*** result_contents ; 
 int /*<<< orphan*/  set_core_autocrlf_to (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stage_content (char**) ; 

void test_merge_workdir_dirty__identical_staged_files_allowed(void)
{
	char **content;
	size_t i;

	set_core_autocrlf_to(repo, false);

	for (i = 0, content = result_contents[i]; content[0]; content = result_contents[++i]) {
		stage_content(content);

		cl_git_pass(git_index_write(repo_index));
		cl_git_pass(merge_branch());
	}
}