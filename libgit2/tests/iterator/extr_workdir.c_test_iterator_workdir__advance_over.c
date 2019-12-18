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
struct TYPE_4__ {int flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;

/* Variables and functions */
 int GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int GIT_ITERATOR_DONT_IGNORE_CASE ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_EMPTY ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_IGNORED ; 
 int /*<<< orphan*/  GIT_ITERATOR_STATUS_NORMAL ; 
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_rewritefile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_advance_over (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 
 int /*<<< orphan*/  p_rmdir (char*) ; 

void test_iterator_workdir__advance_over(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;

	i_opts.flags |= GIT_ITERATOR_DONT_IGNORE_CASE |
		GIT_ITERATOR_DONT_AUTOEXPAND;

	g_repo = cl_git_sandbox_init("icase");

	/* create an empty directory */
	cl_must_pass(p_mkdir("icase/empty", 0777));

	/* create a directory in which all contents are ignored */
	cl_must_pass(p_mkdir("icase/all_ignored", 0777));
	cl_git_rewritefile("icase/all_ignored/one", "This is ignored\n");
	cl_git_rewritefile("icase/all_ignored/two", "This, too, is ignored\n");
	cl_git_rewritefile("icase/all_ignored/.gitignore", ".gitignore\none\ntwo\n");

	/* create a directory in which not all contents are ignored */
	cl_must_pass(p_mkdir("icase/some_ignored", 0777));
	cl_git_rewritefile("icase/some_ignored/one", "This is ignored\n");
	cl_git_rewritefile("icase/some_ignored/two", "This is not ignored\n");
	cl_git_rewritefile("icase/some_ignored/.gitignore", ".gitignore\none\n");

	/* create a directory which has some empty children */
	cl_must_pass(p_mkdir("icase/empty_children", 0777));
	cl_must_pass(p_mkdir("icase/empty_children/empty1", 0777));
	cl_must_pass(p_mkdir("icase/empty_children/empty2", 0777));
	cl_must_pass(p_mkdir("icase/empty_children/empty3", 0777));

	/* create a directory which will disappear! */
	cl_must_pass(p_mkdir("icase/missing_directory", 0777));

	cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));

	cl_must_pass(p_rmdir("icase/missing_directory"));

	expect_advance_over(i, "B", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "D", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "F", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "H", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "J", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "L/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "a", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "all_ignored/", GIT_ITERATOR_STATUS_IGNORED);
	expect_advance_over(i, "c", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "e", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "empty/", GIT_ITERATOR_STATUS_EMPTY);
	expect_advance_over(i, "empty_children/", GIT_ITERATOR_STATUS_EMPTY);
	expect_advance_over(i, "g", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "i", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "k/", GIT_ITERATOR_STATUS_NORMAL);
	expect_advance_over(i, "missing_directory/", GIT_ITERATOR_STATUS_EMPTY);
	expect_advance_over(i, "some_ignored/", GIT_ITERATOR_STATUS_NORMAL);

	cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
	git_iterator_free(i);
}