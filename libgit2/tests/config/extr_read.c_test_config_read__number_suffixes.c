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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_fixture (char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int64 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 

void test_config_read__number_suffixes(void)
{
	git_config *cfg;
	int64_t i;

	cl_git_pass(git_config_open_ondisk(&cfg, cl_fixture("config/config5")));

	cl_git_pass(git_config_get_int64(&i, cfg, "number.simple"));
	cl_assert(i == 1);

	cl_git_pass(git_config_get_int64(&i, cfg, "number.k"));
	cl_assert(i == 1 * 1024);

	cl_git_pass(git_config_get_int64(&i, cfg, "number.kk"));
	cl_assert(i == 1 * 1024);

	cl_git_pass(git_config_get_int64(&i, cfg, "number.m"));
	cl_assert(i == 1 * 1024 * 1024);

	cl_git_pass(git_config_get_int64(&i, cfg, "number.mm"));
	cl_assert(i == 1 * 1024 * 1024);

	cl_git_pass(git_config_get_int64(&i, cfg, "number.g"));
	cl_assert(i == 1 * 1024 * 1024 * 1024);

	cl_git_pass(git_config_get_int64(&i, cfg, "number.gg"));
	cl_assert(i == 1 * 1024 * 1024 * 1024);

	git_config_free(cfg);
}