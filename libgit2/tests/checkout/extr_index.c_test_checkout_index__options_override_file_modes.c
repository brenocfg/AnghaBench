#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct stat {int st_mode; } ;
struct TYPE_4__ {int checkout_strategy; int file_mode; } ;
typedef  TYPE_1__ git_checkout_options ;

/* Variables and functions */
 TYPE_1__ GIT_CHECKOUT_OPTIONS_INIT ; 
 int GIT_CHECKOUT_RECREATE_MISSING ; 
 int GIT_CHECKOUT_SAFE ; 
 int GIT_MODE_PERMS_MASK ; 
 int /*<<< orphan*/  cl_assert_equal_i_fmt (int,int,char*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_is_chmod_supported () ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_checkout_index (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  p_stat (char*,struct stat*) ; 

void test_checkout_index__options_override_file_modes(void)
{
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	struct stat st;

	if (!cl_is_chmod_supported())
		return;

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;
	opts.file_mode = 0700;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	cl_git_pass(p_stat("./testrepo/new.txt", &st));
	cl_assert_equal_i_fmt(st.st_mode & GIT_MODE_PERMS_MASK, 0700, "%07o");
}