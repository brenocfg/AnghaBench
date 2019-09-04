#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  msg; int /*<<< orphan*/  oid_cur; int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEX_ZERO ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_oid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 scalar_t__ git_oid_streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_name_to_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 TYPE_1__* git_reflog_entry_byindex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char const*) ; 

void test_refs_reflog_messages__creating_a_direct_reference(void)
{
	git_reference *reference;
	git_oid id;
	git_reflog *reflog;
	const git_reflog_entry *entry;

	const char *name = "refs/heads/new-head";
	const char *message = "You've been logged, mate!";

	cl_git_pass(git_reference_name_to_id(&id, g_repo, "HEAD"));

	cl_git_pass(git_reference_create(&reference, g_repo, name, &id, 0, message));

	cl_git_pass(git_reflog_read(&reflog, g_repo, name));
	cl_assert_equal_sz(1, git_reflog_entrycount(reflog));

	entry = git_reflog_entry_byindex(reflog, 0);
	cl_assert(git_oid_streq(&entry->oid_old, GIT_OID_HEX_ZERO) == 0);
	cl_assert_equal_oid(&id, &entry->oid_cur);
	cl_assert_equal_s(message, entry->msg);

	git_reflog_free(reflog);
	git_reference_free(reference);
}