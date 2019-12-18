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
 int /*<<< orphan*/  assert_blob_oid (char*,char*) ; 
 int /*<<< orphan*/  assert_commit_message_contains (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__can_include_untracked_files(void)
{
	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, NULL, GIT_STASH_INCLUDE_UNTRACKED));

	assert_commit_message_contains("refs/stash^3", "untracked files on master: ");

	assert_blob_oid("refs/stash^3:what", NULL);
	assert_blob_oid("refs/stash^3:how", NULL);
	assert_blob_oid("refs/stash^3:who", NULL);
	assert_blob_oid("refs/stash^3:when", "b6ed15e81e2593d7bb6265eb4a991d29dc3e628b");
	assert_blob_oid("refs/stash^3:just.ignore", NULL);
}