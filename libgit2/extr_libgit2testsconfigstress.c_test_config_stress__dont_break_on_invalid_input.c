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
 int /*<<< orphan*/  TEST_CONFIG ; 
 int /*<<< orphan*/  buf ; 
 int /*<<< orphan*/  cl_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_exists (int /*<<< orphan*/ ) ; 

void test_config_stress__dont_break_on_invalid_input(void)
{
	git_config *config;

	cl_assert(git_path_exists(TEST_CONFIG));
	cl_git_pass(git_config_open_ondisk(&config, TEST_CONFIG));

	cl_git_pass(git_config_get_string_buf(&buf, config, "color.ui"));
	cl_git_pass(git_config_get_string_buf(&buf, config, "core.editor"));

	git_config_free(config);
}