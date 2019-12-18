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
 int /*<<< orphan*/  cfg ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_snapshot (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  p_unlink (char*) ; 
 int /*<<< orphan*/  snapshot ; 

void test_config_snapshot__includes(void)
{
	int i;

	cl_git_mkfile("including", "[include]\npath = included");
	cl_git_mkfile("included", "[section]\nkey = 1\n");

	cl_git_pass(git_config_open_ondisk(&cfg, "including"));
	cl_git_pass(git_config_snapshot(&snapshot, cfg));

	cl_git_pass(git_config_get_int32(&i, snapshot, "section.key"));
	cl_assert_equal_i(i, 1);

	/* Rewrite "included" config */
	cl_git_mkfile("included", "[section]\nkey = 11\n");

	/* Assert that the live config changed, but snapshot remained the same */
	cl_git_pass(git_config_get_int32(&i, cfg, "section.key"));
	cl_assert_equal_i(i, 11);
	cl_git_pass(git_config_get_int32(&i, snapshot, "section.key"));
	cl_assert_equal_i(i, 1);

	cl_git_pass(p_unlink("including"));
	cl_git_pass(p_unlink("included"));
}