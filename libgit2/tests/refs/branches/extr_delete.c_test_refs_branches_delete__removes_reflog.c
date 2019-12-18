#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_5__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BRANCH_LOCAL ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,scalar_t__) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_branch_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 scalar_t__ git_reference_has_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_reflog_append (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_delete__removes_reflog(void)
{
	git_reference *branch;
	git_reflog *log;
	git_oid oidzero = {{0}};
	git_signature *sig;

	/* Ensure the reflog has at least one entry */
	cl_git_pass(git_signature_now(&sig, "Me", "user@example.com"));
	cl_git_pass(git_reflog_read(&log, repo, "refs/heads/track-local"));
	cl_git_pass(git_reflog_append(log, &oidzero, sig, "message"));
	cl_assert(git_reflog_entrycount(log) > 0);
	git_signature_free(sig);
	git_reflog_free(log);

	cl_git_pass(git_branch_lookup(&branch, repo, "track-local", GIT_BRANCH_LOCAL));
	cl_git_pass(git_branch_delete(branch));
	git_reference_free(branch);

	cl_assert_equal_i(false, git_reference_has_log(repo, "refs/heads/track-local"));

	/* Reading a nonexistant reflog creates it, but it should be empty */
	cl_git_pass(git_reflog_read(&log, repo, "refs/heads/track-local"));
	cl_assert_equal_i(0, git_reflog_entrycount(log));
	git_reflog_free(log);
}