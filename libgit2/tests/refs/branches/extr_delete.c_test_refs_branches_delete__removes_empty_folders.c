#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_signature ;
typedef  int /*<<< orphan*/  git_reflog ;
typedef  int /*<<< orphan*/  git_reference ;
struct TYPE_6__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_7__ {TYPE_1__ member_0; } ;
typedef  TYPE_2__ git_oid ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_REFLOG_DIR ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_create (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_branch_delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_join3 (int /*<<< orphan*/ *,char,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,char const*,char*) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  git_oid_fromstr (TYPE_2__*,char*) ; 
 int git_path_exists (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_append (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ git_reflog_entrycount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reflog_read (int /*<<< orphan*/ **,int /*<<< orphan*/ ,char*) ; 
 char* git_repository_commondir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_signature_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_signature_now (int /*<<< orphan*/ **,char*,char*) ; 
 int /*<<< orphan*/  repo ; 

void test_refs_branches_delete__removes_empty_folders(void)
{
	const char *commondir = git_repository_commondir(repo);
	git_oid commit_id;
	git_commit *commit;
	git_reference *branch;

	git_reflog *log;
	git_oid oidzero = {{0}};
	git_signature *sig;

	git_buf ref_folder = GIT_BUF_INIT;
	git_buf reflog_folder = GIT_BUF_INIT;

	/* Create a new branch with a nested name */
	cl_git_pass(git_oid_fromstr(&commit_id, "a65fedf39aefe402d3bb6e24df4d4f5fe4547750"));
	cl_git_pass(git_commit_lookup(&commit, repo, &commit_id));
	cl_git_pass(git_branch_create(&branch, repo, "some/deep/ref", commit, 0));
	git_commit_free(commit);

	/* Ensure the reflog has at least one entry */
	cl_git_pass(git_signature_now(&sig, "Me", "user@example.com"));
	cl_git_pass(git_reflog_read(&log, repo, "refs/heads/some/deep/ref"));
	cl_git_pass(git_reflog_append(log, &oidzero, sig, "message"));
	cl_assert(git_reflog_entrycount(log) > 0);
	git_signature_free(sig);
	git_reflog_free(log);

	cl_git_pass(git_buf_joinpath(&ref_folder, commondir, "refs/heads/some/deep"));
	cl_git_pass(git_buf_join3(&reflog_folder, '/', commondir, GIT_REFLOG_DIR, "refs/heads/some/deep"));

	cl_assert(git_path_exists(git_buf_cstr(&ref_folder)) == true);
	cl_assert(git_path_exists(git_buf_cstr(&reflog_folder)) == true);

	cl_git_pass(git_branch_delete(branch));

	cl_assert(git_path_exists(git_buf_cstr(&ref_folder)) == false);
	cl_assert(git_path_exists(git_buf_cstr(&reflog_folder)) == false);

	git_reference_free(branch);
	git_buf_dispose(&ref_folder);
	git_buf_dispose(&reflog_folder);
}