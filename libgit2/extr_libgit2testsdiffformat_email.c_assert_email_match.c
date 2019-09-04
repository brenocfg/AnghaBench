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
struct TYPE_4__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  summary; int /*<<< orphan*/  author; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ git_diff_format_email_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
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
 int /*<<< orphan*/  git_oid_fromstr (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  repo ; 

__attribute__((used)) static void assert_email_match(
	const char *expected,
	const char *oidstr,
	git_diff_format_email_options *opts)
{
	git_oid oid;
	git_commit *commit = NULL;
	git_diff *diff = NULL;
	git_buf buf = GIT_BUF_INIT;

	git_oid_fromstr(&oid, oidstr);

	cl_git_pass(git_commit_lookup(&commit, repo, &oid));

	opts->id = git_commit_id(commit);
	opts->author = git_commit_author(commit);
	if (!opts->summary)
		opts->summary = git_commit_summary(commit);

	cl_git_pass(git_diff__commit(&diff, repo, commit, NULL));
	cl_git_pass(git_diff_format_email(&buf, diff, opts));

	cl_assert_equal_s(expected, git_buf_cstr(&buf));
	git_buf_clear(&buf);

	cl_git_pass(git_diff_commit_as_email(
		&buf, repo, commit, 1, 1, opts->flags, NULL));
	cl_assert_equal_s(expected, git_buf_cstr(&buf));

	git_diff_free(diff);
	git_commit_free(commit);
	git_buf_dispose(&buf);
}