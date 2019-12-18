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
typedef  int /*<<< orphan*/  git_repository ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  cl_assert_equal_s (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

void assert_config_entry_value(
	git_repository *repo,
	const char *name,
	const char *expected_value)
{
	git_config *config;
	git_buf buf = GIT_BUF_INIT;

	cl_git_pass(git_repository_config__weakptr(&config, repo));

	cl_git_pass(git_config_get_string_buf(&buf, config, name));

	cl_assert_equal_s(expected_value, git_buf_cstr(&buf));
	git_buf_dispose(&buf);
}