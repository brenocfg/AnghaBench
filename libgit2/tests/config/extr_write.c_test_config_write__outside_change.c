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
 int /*<<< orphan*/  cl_git_mkfile (char const*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 

void test_config_write__outside_change(void)
{
	int32_t tmp;
	git_config *cfg;
	const char *filename = "config-ext-change";

	cl_git_mkfile(filename, "[old]\nvalue = 5\n");

	cl_git_pass(git_config_open_ondisk(&cfg, filename));

	cl_git_pass(git_config_get_int32(&tmp, cfg, "old.value"));

	/* Change the value on the file itself (simulate external process) */
	cl_git_mkfile(filename, "[old]\nvalue = 6\n");

	cl_git_pass(git_config_set_int32(cfg, "new.value", 7));

	cl_git_pass(git_config_get_int32(&tmp, cfg, "old.value"));
	cl_assert_equal_i(6, tmp);

	git_config_free(cfg);
}