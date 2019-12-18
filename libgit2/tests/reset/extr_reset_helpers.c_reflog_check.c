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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  cl_assert_equal_i (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 

void reflog_check(git_repository *repo, const char *refname,
		size_t exp_count, const char *exp_email, const char *exp_msg)
{
	git_reflog *log;
	const git_reflog_entry *entry;

	GIT_UNUSED(exp_email);

	cl_git_pass(git_reflog_read(&log, repo, refname));
	cl_assert_equal_i(exp_count, git_reflog_entrycount(log));
	entry = git_reflog_entry_byindex(log, 0);

	if (exp_msg)
		cl_assert_equal_s(exp_msg, git_reflog_entry_message(entry));

	git_reflog_free(log);
}