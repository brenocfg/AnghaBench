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
typedef  int int32_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_msleep (int) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char const*) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char const*,int) ; 

void test_config_stress__quick_write(void)
{
	git_config *config_w, *config_r;
	const char *path = "./config-quick-write";
	const char *key = "quick.write";
	int32_t i;

	/* Create an external writer for one instance with the other one */
	cl_git_pass(git_config_open_ondisk(&config_w, path));
	cl_git_pass(git_config_open_ondisk(&config_r, path));

	/* Write and read in the same second (repeat to increase the chance of it happening) */
	for (i = 0; i < 10; i++) {
		int32_t val;
		cl_git_pass(git_config_set_int32(config_w, key, i));
		cl_msleep(1);
		cl_git_pass(git_config_get_int32(&val, config_r, key));
		cl_assert_equal_i(i, val);
	}

	git_config_free(config_r);
	git_config_free(config_w);
}