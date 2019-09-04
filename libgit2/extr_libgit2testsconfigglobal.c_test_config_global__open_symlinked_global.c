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
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_default (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  symlink (char*,char*) ; 

void test_config_global__open_symlinked_global(void)
{
#ifndef GIT_WIN32
	git_config *cfg;
	int32_t value;

	cl_git_mkfile("home/.gitconfig.linked", "[global]\n  test = 4567\n");
	cl_must_pass(symlink(".gitconfig.linked", "home/.gitconfig"));

	cl_git_pass(git_config_open_default(&cfg));
	cl_git_pass(git_config_get_int32(&value, cfg, "global.test"));
	cl_assert_equal_i(4567, value);

	git_config_free(cfg);
#endif
}