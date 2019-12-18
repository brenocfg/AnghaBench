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
 int /*<<< orphan*/  cl_assert_equal_s (char*,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  foreach_cb ; 
 int /*<<< orphan*/  git__free (char*) ; 
 int /*<<< orphan*/  git_config_foreach_match (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_string (int /*<<< orphan*/ *,char*,char*) ; 

void test_config_stress__foreach_refreshes(void)
{
	git_config *config_w, *config_r;
	char *value = NULL;

	cl_git_pass(git_config_open_ondisk(&config_w, "./cfg"));
	cl_git_pass(git_config_open_ondisk(&config_r, "./cfg"));

	cl_git_pass(git_config_set_string(config_w, "key.value", "1"));
	cl_git_pass(git_config_foreach_match(config_r, "key.value", foreach_cb, &value));

	cl_assert_equal_s(value, "1");

	git_config_free(config_r);
	git_config_free(config_w);
	git__free(value);
}