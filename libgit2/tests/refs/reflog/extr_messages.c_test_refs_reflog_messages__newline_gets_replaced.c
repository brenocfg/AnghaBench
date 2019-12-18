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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_reflog_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entry_message (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 

void test_refs_reflog_messages__newline_gets_replaced(void)
{
	const git_reflog_entry *entry;
	git_signature *signature;
	git_reflog *reflog;
	git_oid oid;

	cl_git_pass(git_signature_now(&signature, "me", "foo@example.com"));
	cl_git_pass(git_oid_fromstr(&oid, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750"));

	cl_git_pass(git_reflog_read(&reflog, g_repo, "HEAD"));
	cl_assert_equal_sz(7, git_reflog_entrycount(reflog));
	cl_git_pass(git_reflog_append(reflog, &oid, signature, "inner\nnewline"));
	cl_assert_equal_sz(8, git_reflog_entrycount(reflog));

	cl_assert(entry = git_reflog_entry_byindex(reflog, 0));
	cl_assert_equal_s(git_reflog_entry_message(entry), "inner newline");

	git_signature_free(signature);
	git_reflog_free(reflog);
}