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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  assert_config_entry_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  cl_git_pass (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_repo ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 

__attribute__((used)) static void assert_submodule_url(const char* name, const char *url)
{
	git_buf key = GIT_BUF_INIT;


	cl_git_pass(git_buf_printf(&key, "submodule.%s.url", name));
	assert_config_entry_value(g_repo, git_buf_cstr(&key), url);

	git_buf_dispose(&key);
}