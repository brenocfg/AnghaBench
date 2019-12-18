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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_multivar_foreach (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_multivar (int /*<<< orphan*/ *,char const*,char*,char*) ; 

void test_config_multivar__add_new(void)
{
	const char *var = "a.brand.new";
	git_config *cfg;
	int n;

	cl_git_pass(git_config_open_ondisk(&cfg, "config/config11"));

	cl_git_pass(git_config_set_multivar(cfg, var, "$^", "variable"));
	n = 0;
	cl_git_pass(git_config_get_multivar_foreach(cfg, var, NULL, cb, &n));
	cl_assert_equal_i(n, 1);

	git_config_free(cfg);
}