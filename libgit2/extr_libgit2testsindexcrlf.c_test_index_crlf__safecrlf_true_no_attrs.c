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

/* Variables and functions */
 int /*<<< orphan*/  ALL_CRLF_TEXT_RAW ; 
 int /*<<< orphan*/  ALL_LF_TEXT_RAW ; 
 int /*<<< orphan*/  MORE_CRLF_TEXT_RAW ; 
 int /*<<< orphan*/  MORE_LF_TEXT_RAW ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_repo_set_bool (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  g_index ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_index_add_bypath (int /*<<< orphan*/ ,char*) ; 

void test_index_crlf__safecrlf_true_no_attrs(void)
{
	cl_repo_set_bool(g_repo, "core.autocrlf", true);
	cl_repo_set_bool(g_repo, "core.safecrlf", true);

	cl_git_mkfile("crlf/newfile.txt", ALL_LF_TEXT_RAW);
	cl_git_fail(git_index_add_bypath(g_index, "newfile.txt"));

	cl_git_mkfile("crlf/newfile.txt", ALL_CRLF_TEXT_RAW);
	cl_git_pass(git_index_add_bypath(g_index, "newfile.txt"));

	cl_git_mkfile("crlf/newfile.txt", MORE_CRLF_TEXT_RAW);
	cl_git_fail(git_index_add_bypath(g_index, "newfile.txt"));

	cl_git_mkfile("crlf/newfile.txt", MORE_LF_TEXT_RAW);
	cl_git_fail(git_index_add_bypath(g_index, "newfile.txt"));
}