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
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_STASH_DEFAULT ; 
 int /*<<< orphan*/  assert_commit_message_contains (char*,char const*) ; 
 int /*<<< orphan*/  assert_object_oid (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_oid_tostr_s (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_stash_save (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  repo ; 
 int /*<<< orphan*/  signature ; 
 int /*<<< orphan*/  stash_tip_oid ; 

void test_stash_save__multiline_message(void)
{
	const char *msg = "This\n\nis a multiline message\n";
	const git_reflog_entry *entry;
	git_reflog *reflog;

	assert_object_oid("refs/stash@{0}", NULL, GIT_OBJECT_COMMIT);

	cl_git_pass(git_stash_save(&stash_tip_oid, repo, signature, msg, GIT_STASH_DEFAULT));

	cl_git_pass(git_reflog_read(&reflog, repo, "refs/stash"));
	cl_assert(entry = git_reflog_entry_byindex(reflog, 0));
	cl_assert_equal_s(git_reflog_entry_message(entry), "On master: This  is a multiline message");

	assert_object_oid("refs/stash@{0}", git_oid_tostr_s(&stash_tip_oid), GIT_OBJECT_COMMIT);
	assert_commit_message_contains("refs/stash@{0}", msg);

	git_reflog_free(reflog);
}