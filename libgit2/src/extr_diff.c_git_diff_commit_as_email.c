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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_diff_options ;
struct TYPE_4__ {size_t patch_no; size_t total_patches; int /*<<< orphan*/  author; int /*<<< orphan*/  body; int /*<<< orphan*/  summary; int /*<<< orphan*/  id; int /*<<< orphan*/  flags; } ;
typedef  TYPE_1__ git_diff_format_email_options ;
typedef  int /*<<< orphan*/  git_diff ;
typedef  int /*<<< orphan*/  git_commit ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_DIFF_FORMAT_EMAIL_OPTIONS_INIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_commit_author (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_id (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_commit_summary (int /*<<< orphan*/ *) ; 
 int git_diff__commit (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int git_diff_format_email (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_diff_free (int /*<<< orphan*/ *) ; 

int git_diff_commit_as_email(
	git_buf *out,
	git_repository *repo,
	git_commit *commit,
	size_t patch_no,
	size_t total_patches,
	uint32_t flags,
	const git_diff_options *diff_opts)
{
	git_diff *diff = NULL;
	git_diff_format_email_options opts =
		GIT_DIFF_FORMAT_EMAIL_OPTIONS_INIT;
	int error;

	assert (out && repo && commit);

	opts.flags = flags;
	opts.patch_no = patch_no;
	opts.total_patches = total_patches;
	opts.id = git_commit_id(commit);
	opts.summary = git_commit_summary(commit);
	opts.body = git_commit_body(commit);
	opts.author = git_commit_author(commit);

	if ((error = git_diff__commit(&diff, repo, commit, diff_opts)) < 0)
		return error;

	error = git_diff_format_email(out, diff, &opts);

	git_diff_free(diff);
	return error;
}