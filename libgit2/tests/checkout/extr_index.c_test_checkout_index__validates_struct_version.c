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
typedef  TYPE_2__ git_checkout_options ;

/* Variables and functions */
 TYPE_2__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int /*<<< orphan*/  cl_assert_equal_i (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  git_error_clear () ; 
 TYPE_1__* git_error_last () ; 

void test_checkout_index__validates_struct_version(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	const git_error *err;

	opts.version = 1024;
	cl_git_fail(git_checkout_index(g_repo, NULL, &opts));

	err = git_error_last();
	cl_assert_equal_i(err->klass, GIT_ERROR_INVALID);

	opts.version = 0;
	git_error_clear();
	cl_git_fail(git_checkout_index(g_repo, NULL, &opts));

	err = git_error_last();
	cl_assert_equal_i(err->klass, GIT_ERROR_INVALID);
}