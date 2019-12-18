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
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 

void test_config_write__add_section_at_file_with_no_clrf_at_the_end(void)
{
	git_config *cfg;
	int i;

	cl_git_pass(git_config_open_ondisk(&cfg, "config17"));
	cl_git_pass(git_config_set_int32(cfg, "diff.context", 10));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config17"));
	cl_git_pass(git_config_get_int32(&i, cfg, "diff.context"));
	cl_assert_equal_i(10, i);

	git_config_free(cfg);
}