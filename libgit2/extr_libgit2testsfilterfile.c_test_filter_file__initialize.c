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
typedef  int /*<<< orphan*/  git_reference ;
typedef  int /*<<< orphan*/  git_object ;
typedef  int /*<<< orphan*/  git_commit ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_OBJECT_COMMIT ; 
 int /*<<< orphan*/  GIT_RESET_HARD ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_commit_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_reference_peel (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_repository_head (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_reset (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void test_filter_file__initialize(void)
{
	git_reference *head_ref;
	git_commit *head;

	g_repo = cl_git_sandbox_init("crlf");

	cl_git_mkfile("crlf/.gitattributes",
		"*.txt text\n*.bin binary\n*.crlf text eol=crlf\n*.lf text eol=lf\n");

	cl_repo_set_bool(g_repo, "core.autocrlf", true);

	cl_git_pass(git_repository_head(&head_ref, g_repo));
	cl_git_pass(git_reference_peel((git_object **)&head, head_ref, GIT_OBJECT_COMMIT));
	cl_git_pass(git_reset(g_repo, (git_object *)head, GIT_RESET_HARD, NULL));

	git_commit_free(head);
	git_reference_free(head_ref);
}