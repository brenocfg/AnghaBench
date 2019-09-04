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
 int /*<<< orphan*/  cl_assert_equal_b (int,int) ; 
 int /*<<< orphan*/  cl_git_mkfile (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_set_cleanup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clean_test_config ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 

void test_config_read__lone_variable_with_trailing_whitespace(void)
{
	git_config *cfg;
	int b;

	cl_set_cleanup(&clean_test_config, NULL);
	cl_git_mkfile("./testconfig", "[foo]\n    lonevariable   \n");
	cl_git_pass(git_config_open_ondisk(&cfg, "./testconfig"));

	cl_git_pass(git_config_get_bool(&b, cfg, "foo.lonevariable"));
	cl_assert_equal_b(true, b);

	git_config_free(cfg);
}