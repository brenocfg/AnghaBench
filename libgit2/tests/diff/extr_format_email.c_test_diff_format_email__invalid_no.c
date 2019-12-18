#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_oid ;
struct TYPE_4__ {int patch_no; int total_patches; int /*<<< orphan*/  summary; int /*<<< orphan*/  author; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_diff_format_email_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 TYPE_1__ GIT_DIFF_FORMAT_EMAIL_OPTIONS_INIT ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_author (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_lookup (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_summary (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff__commit (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_commit_as_email (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_diff_format_email (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  repo ; 

void test_diff_format_email__invalid_no(void)
{
	git_oid oid;
	git_commit *commit = NULL;
	git_diff *diff = NULL;
	git_diff_format_email_options opts = GIT_DIFF_FORMAT_EMAIL_OPTIONS_INIT;
	git_buf buf = GIT_BUF_INIT;

	git_oid_fromstr(&oid, "9264b96c6d104d0e07ae33d3007b6a48246c6f92");

	cl_git_pass(git_commit_lookup(&commit, repo, &oid));

	opts.id = git_commit_id(commit);
	opts.author = git_commit_author(commit);
	opts.summary = git_commit_summary(commit);
	opts.patch_no = 2;
	opts.total_patches = 1;

	cl_git_pass(git_diff__commit(&diff, repo, commit, NULL));
	cl_git_fail(git_diff_format_email(&buf, diff, &opts));
	cl_git_fail(git_diff_commit_as_email(&buf, repo, commit, 2, 1, 0, NULL));
	cl_git_fail(git_diff_commit_as_email(&buf, repo, commit, 0, 0, 0, NULL));

	git_diff_free(diff);
	git_commit_free(commit);
	git_buf_dispose(&buf);
}