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
 int GIT_STASH_INCLUDE_IGNORED ; 
 int GIT_STASH_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  GIT_STATUS_IGNORED ; 
 int /*<<< orphan*/  GIT_STATUS_WT_NEW ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_ignore_add_rule (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__ignored_directory(void)
{
	cl_git_pass(p_mkdir("stash/ignored_directory", 0777));
	cl_git_pass(p_mkdir("stash/ignored_directory/sub", 0777));
	cl_git_mkfile("stash/ignored_directory/sub/some_file", "stuff");

	assert_status(repo, "ignored_directory/sub/some_file", GIT_STATUS_WT_NEW);
	cl_git_pass(git_ignore_add_rule(repo, "ignored_directory/"));
	assert_status(repo, "ignored_directory/sub/some_file", GIT_STATUS_IGNORED);

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_INCLUDE_UNTRACKED | GIT_STASH_INCLUDE_IGNORED));

	cl_assert(!git_path_exists("stash/ignored_directory/sub/some_file"));
	cl_assert(!git_path_exists("stash/ignored_directory/sub"));
	cl_assert(!git_path_exists("stash/ignored_directory"));
}