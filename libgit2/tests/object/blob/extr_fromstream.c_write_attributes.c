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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GITATTR ; 
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_joinpath (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_futils_mkpath2file (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_repository_path (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void write_attributes(git_repository *repo)
{
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_buf_joinpath(&buf, git_repository_path(repo), "info"));
	cl_git_pass(git_buf_joinpath(&buf, git_buf_cstr(&buf), "attributes"));

	cl_git_pass(git_futils_mkpath2file(git_buf_cstr(&buf), 0777));
	cl_git_rewritefile(git_buf_cstr(&buf), GITATTR);

	git_buf_dispose(&buf);
}