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
typedef  int /*<<< orphan*/  git_describe_result ;
typedef  int /*<<< orphan*/  git_describe_options ;
typedef  int /*<<< orphan*/  git_describe_format_options ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_describe_format (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_describe_result_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_describe_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wildmatch (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void assert_describe_workdir(
	const char *expected_output,
	git_repository *repo,
	git_describe_options *opts,
	git_describe_format_options *fmt_opts)
{
	git_buf label = GIT_BUF_INIT;
	git_describe_result *result;

	cl_git_pass(git_describe_workdir(&result, repo, opts));
	cl_git_pass(git_describe_format(&label, result, fmt_opts));

	cl_must_pass(wildmatch(expected_output, git_buf_cstr(&label), 0));

	git_describe_result_free(result);
	git_buf_dispose(&label);
}