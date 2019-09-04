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
typedef  int /*<<< orphan*/  git_filter_list ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_FILTER_TO_WORKTREE ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_sz (int,size_t) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_filter_list_free (int /*<<< orphan*/ *) ; 
 size_t git_filter_list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_filter_list_load (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void test_filter_custom__can_register_a_custom_filter_in_the_repository(void)
{
	git_filter_list *fl;

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "herofile", GIT_FILTER_TO_WORKTREE, 0));
	/* expect: bitflip, reverse, crlf */
	cl_assert_equal_sz(3, git_filter_list_length(fl));
	git_filter_list_free(fl);

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "herocorp", GIT_FILTER_TO_WORKTREE, 0));
	/* expect: bitflip, reverse - possibly crlf depending on global config */
	{
		size_t flen = git_filter_list_length(fl);
		cl_assert(flen == 2 || flen == 3);
	}
	git_filter_list_free(fl);

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "hero.bin", GIT_FILTER_TO_WORKTREE, 0));
	/* expect: bitflip, reverse */
	cl_assert_equal_sz(2, git_filter_list_length(fl));
	git_filter_list_free(fl);

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "heroflip", GIT_FILTER_TO_WORKTREE, 0));
	/* expect: bitflip (because of -reverse) */
	cl_assert_equal_sz(1, git_filter_list_length(fl));
	git_filter_list_free(fl);

	cl_git_pass(git_filter_list_load(
		&fl, g_repo, NULL, "doesntapplytome.bin",
		GIT_FILTER_TO_WORKTREE, 0));
	/* expect: none */
	cl_assert_equal_sz(0, git_filter_list_length(fl));
	git_filter_list_free(fl);
}