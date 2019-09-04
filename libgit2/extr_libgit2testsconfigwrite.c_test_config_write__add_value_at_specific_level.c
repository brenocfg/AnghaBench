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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_LOCAL ; 
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_assert_equal_b (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_add_file_ondisk (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_bool (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_int64 (scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_config_open_level (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_bool (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_int64 (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 

void test_config_write__add_value_at_specific_level(void)
{
	git_config *cfg, *cfg_specific;
	int i;
	int64_t l, expected = +9223372036854775803;
	git_buf buf = GIT_BUF_INIT;

	/* open config15 as global level config file */
	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, "config9",
		GIT_CONFIG_LEVEL_LOCAL, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, "config15",
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));

	cl_git_pass(git_config_open_level(&cfg_specific, cfg, GIT_CONFIG_LEVEL_GLOBAL));

	cl_git_pass(git_config_set_int32(cfg_specific, "core.int32global", 28));
	cl_git_pass(git_config_set_int64(cfg_specific, "core.int64global", expected));
	cl_git_pass(git_config_set_bool(cfg_specific, "core.boolglobal", true));
	cl_git_pass(git_config_set_string(cfg_specific, "core.stringglobal", "I'm a global config value!"));
	git_config_free(cfg_specific);
	git_config_free(cfg);

	/* open config15 as local level config file */
	cl_git_pass(git_config_open_ondisk(&cfg, "config15"));

	cl_git_pass(git_config_get_int32(&i, cfg, "core.int32global"));
	cl_assert_equal_i(28, i);
	cl_git_pass(git_config_get_int64(&l, cfg, "core.int64global"));
	cl_assert(l == expected);
	cl_git_pass(git_config_get_bool(&i, cfg, "core.boolglobal"));
	cl_assert_equal_b(true, i);
	cl_git_pass(git_config_get_string_buf(&buf, cfg, "core.stringglobal"));
	cl_assert_equal_s("I'm a global config value!", git_buf_cstr(&buf));

	git_buf_dispose(&buf);
	git_config_free(cfg);
}