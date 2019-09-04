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
 int /*<<< orphan*/  _name ; 
 int /*<<< orphan*/  cl_assert_equal_i (int,int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_iterator_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_multivar_iterator_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ git_config_next (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_get_multivar(git_config *cfg, int expected)
{
	git_config_iterator *iter;
	git_config_entry *entry;
	int n = 0;

	cl_git_pass(git_config_multivar_iterator_new(&iter, cfg, _name, NULL));

	while (git_config_next(&entry, iter) == 0)
		n++;

	cl_assert_equal_i(expected, n);
	git_config_iterator_free(iter);

}