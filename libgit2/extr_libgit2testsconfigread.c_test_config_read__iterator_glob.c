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
 int /*<<< orphan*/  check_glob_iter (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_read__iterator_glob(void)
{
	git_config *cfg;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config9")));

	check_glob_iter(cfg, "core.*", 3);
	check_glob_iter(cfg, "remote\\.ab.*", 2);
	check_glob_iter(cfg, ".*url$", 2);
	check_glob_iter(cfg, ".*dummy.*", 2);
	check_glob_iter(cfg, ".*nomatch.*", 0);

	git_config_free(cfg);
}