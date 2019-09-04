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
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_iterator_glob_new (int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_read__iterator_invalid_glob(void)
{
	git_config *cfg;
	git_config_iterator *iter;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config9")));

	cl_git_fail(git_config_iterator_glob_new(&iter, cfg, "*"));

	git_config_free(cfg);
}