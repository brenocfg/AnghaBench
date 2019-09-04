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
typedef  int /*<<< orphan*/  git_config_iterator ;
typedef  int /*<<< orphan*/  git_config_entry ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int GIT_ITEROVER ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char const*) ; 
 int git_config_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_glob_iter(git_config *cfg, const char *regexp, int expected)
{
	git_config_iterator *iter;
	git_config_entry *entry;
	int count, error;

	cl_git_pass(git_config_iterator_glob_new(&iter, cfg, regexp));

	count = 0;
	while ((error = git_config_next(&entry, iter)) == 0)
		count++;

	cl_assert_equal_i(GIT_ITEROVER, error);
	cl_assert_equal_i(expected, count);
	git_config_iterator_free(iter);
}