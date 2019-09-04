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
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_read__case_sensitive(void)
{
	git_config *cfg;
	int i;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config1")));

	cl_git_pass(git_config_get_string_buf(&buf, cfg, "this.that.other"));
	cl_assert_equal_s("true", git_buf_cstr(&buf));
	git_buf_clear(&buf);

	cl_git_pass(git_config_get_string_buf(&buf, cfg, "this.That.other"));
	cl_assert_equal_s("yes", git_buf_cstr(&buf));

	cl_git_pass(git_config_get_bool(&i, cfg, "this.that.other"));
	cl_assert(i == 1);
	cl_git_pass(git_config_get_bool(&i, cfg, "this.That.other"));
	cl_assert(i == 1);

	/* This one doesn't exist */
	cl_must_fail(git_config_get_bool(&i, cfg, "this.thaT.other"));

	git_config_free(cfg);
}