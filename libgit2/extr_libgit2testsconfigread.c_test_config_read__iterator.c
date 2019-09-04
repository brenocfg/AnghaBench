#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_config_iterator ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_GLOBAL ; 
 int /*<<< orphan*/  GIT_CONFIG_LEVEL_SYSTEM ; 
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_assert_equal_s (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_add_file_ondisk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int git_config_next (TYPE_1__**,int /*<<< orphan*/ *) ; 

void test_config_read__iterator(void)
{
	const char *keys[] = {
		"core.dummy2",
		"core.verylong",
		"core.dummy",
		"remote.ab.url",
		"remote.abba.url",
		"core.dummy2",
		"core.global"
	};
	git_config *cfg;
	git_config_iterator *iter;
	git_config_entry *entry;
	int count, ret;

	cl_git_pass(git_config_new(&cfg));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config9"),
		GIT_CONFIG_LEVEL_SYSTEM, NULL, 0));
	cl_git_pass(git_config_add_file_ondisk(cfg, cl_fixture("config/config15"),
		GIT_CONFIG_LEVEL_GLOBAL, NULL, 0));

	count = 0;
	cl_git_pass(git_config_iterator_new(&iter, cfg));

	while ((ret = git_config_next(&entry, iter)) == 0) {
		cl_assert_equal_s(entry->name, keys[count]);
		count++;
	}

	git_config_iterator_free(iter);
	cl_assert_equal_i(GIT_ITEROVER, ret);
	cl_assert_equal_i(7, count);

	count = 3;
	cl_git_pass(git_config_iterator_new(&iter, cfg));

	git_config_iterator_free(iter);
	git_config_free(cfg);
}