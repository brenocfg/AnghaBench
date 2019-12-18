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
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (size_t,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 size_t git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 

void test_refs_reflog_reflog__append_to_HEAD_when_changing_current_branch(void)
{
	size_t nlogs, nlogs_after;
	git_reference *ref;
	git_reflog *log;
	git_oid id;

	cl_git_pass(git_reflog_read(&log, g_repo, "HEAD"));
	nlogs = git_reflog_entrycount(log);
	git_reflog_free(log);

	/* Move it back */
	git_oid_fromstr(&id, "be3563ae3f795b2b4353bcce3a527ad0a4f7f644");
	cl_git_pass(git_reference_create(&ref, g_repo, "refs/heads/master", &id, 1, NULL));
	git_reference_free(ref);

	cl_git_pass(git_reflog_read(&log, g_repo, "HEAD"));
	nlogs_after = git_reflog_entrycount(log);
	git_reflog_free(log);

	cl_assert_equal_i(nlogs_after, nlogs + 1);
}