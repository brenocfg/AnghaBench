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
 int /*<<< orphan*/  _name ; 
 int /*<<< orphan*/  cb ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_delete_multivar (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_multivar_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 

void test_config_multivar__delete(void)
{
	git_config *cfg;
	int n;

	cl_git_pass(git_config_open_ondisk(&cfg, "config/config11"));

	n = 0;
	cl_git_pass(git_config_get_multivar_foreach(cfg, _name, NULL, cb, &n));
	cl_assert_equal_i(2, n);

	cl_git_pass(git_config_delete_multivar(cfg, _name, "github"));

	n = 0;
	cl_git_pass(git_config_get_multivar_foreach(cfg, _name, NULL, cb, &n));
	cl_assert_equal_i(1, n);

	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config/config11"));

	n = 0;
	cl_git_pass(git_config_get_multivar_foreach(cfg, _name, NULL, cb, &n));
	cl_assert_equal_i(1, n);

	git_config_free(cfg);
}