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
typedef  scalar_t__ int64_t ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 int /*<<< orphan*/  cl_assert (int) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_must_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_int32 (int*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_get_int64 (scalar_t__*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  git_config_open_ondisk (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  git_config_set_int32 (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  git_config_set_int64 (int /*<<< orphan*/ *,char*,int) ; 

void test_config_write__replace_value(void)
{
	git_config *cfg;
	int i;
	int64_t l, expected = +9223372036854775803;

	/* By freeing the config, we make sure we flush the values  */
	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_set_int32(cfg, "core.dummy", 5));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_get_int32(&i, cfg, "core.dummy"));
	cl_assert(i == 5);
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_set_int32(cfg, "core.dummy", 1));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_set_int64(cfg, "core.verylong", expected));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_get_int64(&l, cfg, "core.verylong"));
	cl_assert(l == expected);
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_must_fail(git_config_get_int32(&i, cfg, "core.verylong"));
	git_config_free(cfg);

	cl_git_pass(git_config_open_ondisk(&cfg, "config9"));
	cl_git_pass(git_config_set_int64(cfg, "core.verylong", 1));
	git_config_free(cfg);
}