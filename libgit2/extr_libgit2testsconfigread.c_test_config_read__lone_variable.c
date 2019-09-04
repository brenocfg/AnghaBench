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
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_read__lone_variable(void)
{
	git_config *cfg;
	int i;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config4")));

	cl_git_fail(git_config_get_int32(&i, cfg, "some.section.variable"));

	cl_git_pass(git_config_get_string_buf(&buf, cfg, "some.section.variable"));
	cl_assert_equal_s("", git_buf_cstr(&buf));
	git_buf_clear(&buf);

	cl_git_pass(git_config_get_bool(&i, cfg, "some.section.variable"));
	cl_assert(i == 1);

	cl_git_pass(git_config_get_string_buf(&buf, cfg, "some.section.variableeq"));
	cl_assert_equal_s("", git_buf_cstr(&buf));

	cl_git_pass(git_config_get_bool(&i, cfg, "some.section.variableeq"));
	cl_assert(i == 0);

	git_config_free(cfg);
}