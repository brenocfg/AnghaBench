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
 int /*<<< orphan*/  GIT_FILEBUF_INIT ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_win32__hidden (int*,char*) ; 
 int /*<<< orphan*/  git_win32__set_hidden (char*,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_core_filebuf__hidden_file(void)
{
#ifndef GIT_WIN32
	cl_skip();
#else
	git_filebuf file = GIT_FILEBUF_INIT;
	char *dir = "hidden", *test = "hidden/test";
	bool hidden;

	cl_git_pass(p_mkdir(dir, 0666));
	cl_git_mkfile(test, "dummy content");

	cl_git_pass(git_win32__set_hidden(test, true));
	cl_git_pass(git_win32__hidden(&hidden, test));
	cl_assert(hidden);

	cl_git_pass(git_filebuf_open(&file, test, 0, 0666));

	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));

	cl_git_pass(git_filebuf_commit(&file));

	git_filebuf_cleanup(&file);
#endif
}