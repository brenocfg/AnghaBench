#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int count; char** strings; } ;
struct TYPE_6__ {int flags; TYPE_1__ pathspec; } ;
typedef  TYPE_2__ git_status_options ;
typedef  int /*<<< orphan*/  git_repository ;

/* Variables and functions */
 TYPE_2__ GIT_STATUS_OPTIONS_INIT ; 
 int GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH ; 
 int GIT_STATUS_OPT_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  cb_status__expected_path ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  cleanup_new_repo ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_init (int /*<<< orphan*/ **,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_status_foreach_ext (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

void test_status_worktree_init__disable_pathspec_match(void)
{
	git_repository *repo;
	git_status_options opts = GIT_STATUS_OPTIONS_INIT;
	char *file_with_bracket = "LICENSE[1].md", 
		*imaginary_file_with_bracket = "LICENSE[1-2].md";

	cl_set_cleanup(&cleanup_new_repo, "pathspec");
	cl_git_pass(git_repository_init(&repo, "pathspec", 0));
	cl_git_mkfile("pathspec/LICENSE[1].md", "screaming bracket\n");
	cl_git_mkfile("pathspec/LICENSE1.md", "no bracket\n");

	opts.flags = GIT_STATUS_OPT_INCLUDE_UNTRACKED | 
		GIT_STATUS_OPT_DISABLE_PATHSPEC_MATCH;
	opts.pathspec.count = 1;
	opts.pathspec.strings = &file_with_bracket;

	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__expected_path, 
		file_with_bracket)
	);

	/* Test passing a pathspec matching files in the workdir. */
	/* Must not match because pathspecs are disabled. */ 
	opts.pathspec.strings = &imaginary_file_with_bracket;
	cl_git_pass(
		git_status_foreach_ext(repo, &opts, cb_status__expected_path, NULL)
	);

	git_repository_free(repo);
}