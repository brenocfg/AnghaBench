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
 int /*<<< orphan*/  GIT_REFS_HEADS_DIR ; 
 int /*<<< orphan*/  git_buf_cstr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_printf (int /*<<< orphan*/ *,char const*,char const*) ; 
 int git_config_get_string_buf (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int retrieve_upstream_configuration(
	git_buf *out,
	const git_config *config,
	const char *canonical_branch_name,
	const char *format)
{
	git_buf buf = GIT_BUF_INIT;
	int error;

	if (git_buf_printf(&buf, format,
		canonical_branch_name + strlen(GIT_REFS_HEADS_DIR)) < 0)
			return -1;

	error = git_config_get_string_buf(out, config, git_buf_cstr(&buf));
	git_buf_dispose(&buf);
	return error;
}