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
 int /*<<< orphan*/  EMPTY_TREE ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_OBJECT_TREE ; 
 int /*<<< orphan*/  GIT_STASH_INCLUDE_UNTRACKED ; 
 int GIT_STATUS_IGNORED ; 
 int GIT_STATUS_INDEX_MODIFIED ; 
 int GIT_STATUS_WT_MODIFIED ; 
 int /*<<< orphan*/  assert_object_oid (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_status (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__including_untracked_without_any_untracked_file_creates_an_empty_tree(void)
{
	cl_must_pass(p_unlink("stash/when"));

	assert_status(repo, "what", GIT_STATUS_WT_MODIFIED | GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "how", GIT_STATUS_INDEX_MODIFIED);
	assert_status(repo, "who", GIT_STATUS_WT_MODIFIED);
	assert_status(repo, "when", GIT_ENOTFOUND);
	assert_status(repo, "just.ignore", GIT_STATUS_IGNORED);

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_INCLUDE_UNTRACKED));

	assert_object_oid("stash^3^{tree}", EMPTY_TREE, GIT_OBJECT_TREE);
}