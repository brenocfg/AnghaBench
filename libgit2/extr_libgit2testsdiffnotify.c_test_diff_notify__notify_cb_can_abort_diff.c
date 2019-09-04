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
struct TYPE_5__ {char** strings; int count; } ;
struct TYPE_6__ {int flags; TYPE_1__ pathspec; int /*<<< orphan*/  notify_cb; } ;
typedef  TYPE_2__ git_diff_options ;
typedef  int /*<<< orphan*/  git_diff ;

/* Variables and functions */
 int GIT_DIFF_INCLUDE_IGNORED ; 
 int GIT_DIFF_INCLUDE_UNTRACKED ; 
 TYPE_2__ GIT_DIFF_OPTIONS_INIT ; 
 int /*<<< orphan*/  abort_diff ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_diff_index_to_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 

void test_diff_notify__notify_cb_can_abort_diff(void)
{
	git_diff_options opts = GIT_DIFF_OPTIONS_INIT;
	git_diff *diff = NULL;
	char *pathspec = NULL;

	g_repo = cl_git_sandbox_init("status");

	opts.flags |= GIT_DIFF_INCLUDE_IGNORED | GIT_DIFF_INCLUDE_UNTRACKED;
	opts.notify_cb = abort_diff;
	opts.pathspec.strings = &pathspec;
	opts.pathspec.count   = 1;

	pathspec = "file_deleted";
	cl_git_fail_with(
		git_diff_index_to_workdir(&diff, g_repo, NULL, &opts), -42);

	pathspec = "staged_changes_modified_file";
	cl_git_fail_with(
		git_diff_index_to_workdir(&diff, g_repo, NULL, &opts), -42);
}