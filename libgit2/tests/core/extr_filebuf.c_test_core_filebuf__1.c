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
typedef  int /*<<< orphan*/  git_filebuf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILEBUF_APPEND ; 
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_file (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 

void test_core_filebuf__1(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	char test[] = "test";

	cl_git_mkfile(test, "libgit2 rocks\n");

	cl_git_pass(git_filebuf_open(&file, test, GIT_FILEBUF_APPEND, 0666));
	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));
	cl_git_pass(git_filebuf_commit(&file));

	cl_assert_equal_file("libgit2 rocks\nlibgit2 rocks\n", 0, test);

	cl_must_pass(p_unlink(test));
}