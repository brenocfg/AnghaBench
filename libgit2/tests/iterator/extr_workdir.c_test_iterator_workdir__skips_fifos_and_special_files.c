#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; } ;
typedef  TYPE_1__ git_iterator_options ;
typedef  int /*<<< orphan*/  git_iterator ;
struct TYPE_7__ {int /*<<< orphan*/  mode; } ;
typedef  TYPE_2__ git_index_entry ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int GIT_ITERATOR_DONT_AUTOEXPAND ; 
 int GIT_ITERATOR_INCLUDE_TREES ; 
 TYPE_1__ GIT_ITERATOR_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int S_ISDIR (int /*<<< orphan*/ ) ; 
 int S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_skip () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_advance (TYPE_2__ const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_filesystem (int /*<<< orphan*/ **,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mkfifo (char*,int) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_iterator_workdir__skips_fifos_and_special_files(void)
{
#ifndef GIT_WIN32
	git_iterator *i;
	const git_index_entry *e;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;

	g_repo = cl_git_sandbox_init("empty_standard_repo");

	cl_must_pass(p_mkdir("empty_standard_repo/dir", 0777));
	cl_git_mkfile("empty_standard_repo/file", "not me");

	cl_assert(!mkfifo("empty_standard_repo/fifo", 0777));
	cl_assert(!access("empty_standard_repo/fifo", F_OK));

	i_opts.flags = GIT_ITERATOR_INCLUDE_TREES |
		GIT_ITERATOR_DONT_AUTOEXPAND;

	cl_git_pass(git_iterator_for_filesystem(
		&i, "empty_standard_repo", &i_opts));

	cl_git_pass(git_iterator_advance(&e, i)); /* .git */
	cl_assert(S_ISDIR(e->mode));
	cl_git_pass(git_iterator_advance(&e, i)); /* dir */
	cl_assert(S_ISDIR(e->mode));
	/* skips fifo */
	cl_git_pass(git_iterator_advance(&e, i)); /* file */
	cl_assert(S_ISREG(e->mode));

	cl_assert_equal_i(GIT_ITEROVER, git_iterator_advance(&e, i));

	git_iterator_free(i);
#else
	cl_skip();
#endif
}