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
 int /*<<< orphan*/  GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_git_fail_with (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_sandbox_init (char*) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expect_advance_into (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_iterator_advance (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_iterator_for_workdir (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  git_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  p_mkdir (char*,int) ; 

void test_iterator_workdir__advance_into(void)
{
	git_iterator *i;
	git_iterator_options i_opts = GIT_ITERATOR_OPTIONS_INIT;

	g_repo = cl_git_sandbox_init("icase");

	i_opts.flags |= GIT_ITERATOR_DONT_IGNORE_CASE |
		GIT_ITERATOR_DONT_AUTOEXPAND;

	cl_must_pass(p_mkdir("icase/Empty", 0777));

	cl_git_pass(git_iterator_for_workdir(&i, g_repo, NULL, NULL, &i_opts));
	expect_advance_into(i, "B");
	expect_advance_into(i, "D");
	expect_advance_into(i, "Empty/");
	expect_advance_into(i, "F");
	expect_advance_into(i, "H");
	expect_advance_into(i, "J");
	expect_advance_into(i, "L/");
	expect_advance_into(i, "L/1");
	expect_advance_into(i, "L/B");
	expect_advance_into(i, "L/D");
	expect_advance_into(i, "L/a");
	expect_advance_into(i, "L/c");
	expect_advance_into(i, "a");
	expect_advance_into(i, "c");
	expect_advance_into(i, "e");
	expect_advance_into(i, "g");
	expect_advance_into(i, "i");
	expect_advance_into(i, "k/");
	expect_advance_into(i, "k/1");
	expect_advance_into(i, "k/B");
	expect_advance_into(i, "k/D");
	expect_advance_into(i, "k/a");
	expect_advance_into(i, "k/c");

	cl_git_fail_with(GIT_ITEROVER, git_iterator_advance(NULL, i));
	git_iterator_free(i);
}