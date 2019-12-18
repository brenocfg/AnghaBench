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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 

void test_config_write__write_subsection(void)
{
	git_config *cfg;
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_set_string(cfg, "my.own.var", "works"));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "my.own.var"));
	cl_assert_equal_s("works", git_buf_cstr(&buf));

	git_buf_dispose(&buf);
	git_config_free(cfg);
}