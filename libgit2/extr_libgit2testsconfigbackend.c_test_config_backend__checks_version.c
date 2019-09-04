#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  klass; } ;
typedef  TYPE_1__ git_error ;
struct TYPE_7__ {int version; } ;
typedef  TYPE_2__ git_config_backend ;
typedef  int /*<<< orphan*/  git_config ;

/* Variables and functions */
 TYPE_2__ GIT_CONFIG_BACKEND_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_config_add_backend (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  git_config_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_new (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 

void test_config_backend__checks_version(void)
{
	git_config *cfg;
	git_config_backend backend = GIT_CONFIG_BACKEND_INIT;
	const git_error *err;

	backend.version = 1024;

	cl_git_pass(git_config_new(&cfg));
	cl_git_fail(git_config_add_backend(cfg, &backend, 0, NULL, false));
	err = git_error_last();
	cl_assert_equal_i(GIT_ERROR_INVALID, err->klass);

	git_error_clear();
	backend.version = 1024;
	cl_git_fail(git_config_add_backend(cfg, &backend, 0, NULL, false));
	err = git_error_last();
	cl_assert_equal_i(GIT_ERROR_INVALID, err->klass);

	git_config_free(cfg);
}