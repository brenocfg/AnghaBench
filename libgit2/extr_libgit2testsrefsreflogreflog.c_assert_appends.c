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
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_3__ {int /*<<< orphan*/ * msg; int /*<<< orphan*/  oid_cur; int /*<<< orphan*/  committer; int /*<<< orphan*/  oid_old; } ;
typedef  TYPE_1__ git_reflog_entry ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_oid ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OID_HEX_ZERO ; 
 int /*<<< orphan*/  assert_signature (int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  commit_msg ; 
 scalar_t__ git_oid_cmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 scalar_t__ git_oid_streq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_1__* git_reflog_entry_byindex (int /*<<< orphan*/ *,int) ; 
 scalar_t__ git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_repository_open (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  new_ref ; 

__attribute__((used)) static void assert_appends(const git_signature *committer, const git_oid *oid)
{
	git_repository *repo2;
	git_reference *lookedup_ref;
	git_reflog *reflog;
	const git_reflog_entry *entry;

	/* Reopen a new instance of the repository */
	cl_git_pass(git_repository_open(&repo2, "testrepo.git"));

	/* Lookup the previously created branch */
	cl_git_pass(git_reference_lookup(&lookedup_ref, repo2, new_ref));

	/* Read and parse the reflog for this branch */
	cl_git_pass(git_reflog_read(&reflog, repo2, new_ref));
	cl_assert_equal_i(3, (int)git_reflog_entrycount(reflog));

	/* The first one was the creation of the branch */
	entry = git_reflog_entry_byindex(reflog, 2);
	cl_assert(git_oid_streq(&entry->oid_old, GIT_OID_HEX_ZERO) == 0);

	entry = git_reflog_entry_byindex(reflog, 1);
	assert_signature(committer, entry->committer);
	cl_assert(git_oid_cmp(oid, &entry->oid_old) == 0);
	cl_assert(git_oid_cmp(oid, &entry->oid_cur) == 0);
	cl_assert(entry->msg == NULL);

	entry = git_reflog_entry_byindex(reflog, 0);
	assert_signature(committer, entry->committer);
	cl_assert(git_oid_cmp(oid, &entry->oid_cur) == 0);
	cl_assert_equal_s(commit_msg, entry->msg);

	git_reflog_free(reflog);
	git_repository_free(repo2);

	git_reference_free(lookedup_ref);
}