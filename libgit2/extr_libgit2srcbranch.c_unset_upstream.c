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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_BUF_INIT ; 
 int /*<<< orphan*/  git_buf_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ git_config_delete_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int unset_upstream(git_config *config, const char *shortname)
{
	git_buf buf = GIT_BUF_INIT;

	if (git_buf_printf(&buf, "branch.%s.remote", shortname) < 0)
		return -1;

	if (git_config_delete_entry(config, git_buf_cstr(&buf)) < 0)
		goto on_error;

	git_buf_clear(&buf);
	if (git_buf_printf(&buf, "branch.%s.merge", shortname) < 0)
		goto on_error;

	if (git_config_delete_entry(config, git_buf_cstr(&buf)) < 0)
		goto on_error;

	git_buf_dispose(&buf);
	return 0;

on_error:
	git_buf_dispose(&buf);
	return -1;
}