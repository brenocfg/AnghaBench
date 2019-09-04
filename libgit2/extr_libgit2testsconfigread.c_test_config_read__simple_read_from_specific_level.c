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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_add_file_ondisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_int64 (scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_config_open_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void test_config_read__simple_read_from_specific_level(void)
{
	git_config *cfg, *cfg_specific;
	int i;
	int64_t l, expected = +9223372036854775803;

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config18"),
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config19"),
		GIT_CONFIG_LEVEL_SYSTEM, NULL, 0));

	cl_git_pass(git_config_open_level(&cfg_specific, cfg, GIT_CONFIG_LEVEL_GLOBAL));

	cl_git_pass(git_config_get_int32(&i, cfg_specific, "core.int32global"));
	cl_assert_equal_i(28, i);
	cl_git_pass(git_config_get_int64(&l, cfg_specific, "core.int64global"));
	cl_assert(l == expected);
	cl_git_pass(git_config_get_bool(&i, cfg_specific, "core.boolglobal"));
	cl_assert_equal_b(true, i);
	cl_git_pass(git_config_get_string_buf(&buf, cfg_specific, "core.stringglobal"));
	cl_assert_equal_s("I'm a global config value!", git_buf_cstr(&buf));

	git_config_free(cfg_specific);
	git_config_free(cfg);
}