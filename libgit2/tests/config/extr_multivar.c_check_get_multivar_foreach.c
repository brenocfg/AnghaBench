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
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  _name ; 
 int /*<<< orphan*/  cb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int) ; 
 int git_config_get_multivar_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void check_get_multivar_foreach(
	git_config *cfg, int expected, int expected_patterned)
{
	int n = 0;

	if (expected > 0) {
		cl_git_pass(git_config_get_multivar_foreach(cfg, _name, NULL, cb, &n));
		cl_assert_equal_i(expected, n);
	} else {
		cl_assert_equal_i(GIT_ENOTFOUND,
			git_config_get_multivar_foreach(cfg, _name, NULL, cb, &n));
	}

	n = 0;

	if (expected_patterned > 0) {
		cl_git_pass(git_config_get_multivar_foreach(cfg, _name, "example", cb, &n));
		cl_assert_equal_i(expected_patterned, n);
	} else {
		cl_assert_equal_i(GIT_ENOTFOUND,
			git_config_get_multivar_foreach(cfg, _name, "example", cb, &n));
	}
}