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
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  git_filebuf_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filebuf_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_filebuf_printf (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  git_path_exists (char*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int p_open (char*,int /*<<< orphan*/ ) ; 

void test_core_filebuf__rename_error(void)
{
	git_filebuf file = GIT_FILEBUF_INIT;
	char *dir = "subdir",  *test = "subdir/test", *test_lock = "subdir/test.lock";
	int fd;

#ifndef GIT_WIN32
	cl_skip();
#endif

	cl_git_pass(p_mkdir(dir, 0666));
	cl_git_mkfile(test, "dummy content");
	fd = p_open(test, O_RDONLY);
	cl_assert(fd > 0);
	cl_git_pass(git_filebuf_open(&file, test, 0, 0666));

	cl_git_pass(git_filebuf_printf(&file, "%s\n", "libgit2 rocks"));

	cl_assert_equal_i(true, git_path_exists(test_lock));

	cl_git_fail(git_filebuf_commit(&file));
	p_close(fd);

	git_filebuf_cleanup(&file);

	cl_assert_equal_i(false, git_path_exists(test_lock));
}