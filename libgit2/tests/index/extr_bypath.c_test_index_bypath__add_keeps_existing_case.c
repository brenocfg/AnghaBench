#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (TYPE_1__ const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_repo_get_bool (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  clar__skip () ; 
 int /*<<< orphan*/  g_idx ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_index_get_bypath (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

void test_index_bypath__add_keeps_existing_case(void)
{
	const git_index_entry *entry;

	if (!cl_repo_get_bool(g_repo, "core.ignorecase"))
		clar__skip();

	cl_git_mkfile("submod2/just_a_dir/file1.txt", "This is a file");
	cl_git_pass(git_index_add_bypath(g_idx, "just_a_dir/file1.txt"));

	cl_assert(entry = git_index_get_bypath(g_idx, "just_a_dir/file1.txt", 0));
	cl_assert_equal_s("just_a_dir/file1.txt", entry->path);

	cl_git_rewritefile("submod2/just_a_dir/file1.txt", "Updated!");
	cl_git_pass(git_index_add_bypath(g_idx, "just_a_dir/FILE1.txt"));

	cl_assert(entry = git_index_get_bypath(g_idx, "just_a_dir/FILE1.txt", 0));
	cl_assert_equal_s("just_a_dir/file1.txt", entry->path);
}