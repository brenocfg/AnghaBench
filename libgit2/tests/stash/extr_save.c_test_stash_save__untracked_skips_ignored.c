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
 int /*<<< orphan*/  GIT_STASH_INCLUDE_UNTRACKED ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_append2file (char*,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int git_path_exists (char*) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__untracked_skips_ignored(void)
{
	cl_git_append2file("stash/.gitignore", "bundle/vendor/\n");
	cl_must_pass(p_mkdir("stash/bundle", 0777));
	cl_must_pass(p_mkdir("stash/bundle/vendor", 0777));
	cl_git_mkfile("stash/bundle/vendor/blah", "contents\n");

	cl_assert(git_path_exists("stash/when")); /* untracked */
	cl_assert(git_path_exists("stash/just.ignore")); /* ignored */
	cl_assert(git_path_exists("stash/bundle/vendor/blah")); /* ignored */

	cl_git_pass(git_stash_save(
		&stash_tip_oid, repo, signature, NULL, GIT_STASH_INCLUDE_UNTRACKED));

	cl_assert(!git_path_exists("stash/when"));
	cl_assert(git_path_exists("stash/bundle/vendor/blah"));
	cl_assert(git_path_exists("stash/just.ignore"));
}