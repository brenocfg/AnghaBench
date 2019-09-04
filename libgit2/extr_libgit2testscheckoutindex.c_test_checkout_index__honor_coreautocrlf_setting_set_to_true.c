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

/* Variables and functions */

void test_checkout_index__honor_coreautocrlf_setting_set_to_true(void)
{
#ifdef GIT_WIN32
	git_checkout_options opts = GIT_CHECKOUT_OPTIONS_INIT;
	const char *expected_readme_text = "hey there\r\n";

	cl_git_pass(p_unlink("./testrepo/.gitattributes"));
	cl_repo_set_bool(g_repo, "core.autocrlf", true);

	opts.checkout_strategy = GIT_CHECKOUT_SAFE | GIT_CHECKOUT_RECREATE_MISSING;

	cl_git_pass(git_checkout_index(g_repo, NULL, &opts));

	check_file_contents("./testrepo/README", expected_readme_text);
#endif
}