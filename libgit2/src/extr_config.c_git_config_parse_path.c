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
 int /*<<< orphan*/  GIT_ERROR_CONFIG ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int git_buf_sets (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_sysdir_expand_global_file (int /*<<< orphan*/ *,char const*) ; 

int git_config_parse_path(git_buf *out, const char *value)
{
	assert(out && value);

	git_buf_sanitize(out);

	if (value[0] == '~') {
		if (value[1] != '\0' && value[1] != '/') {
			git_error_set(GIT_ERROR_CONFIG, "retrieving a homedir by name is not supported");
			return -1;
		}

		return git_sysdir_expand_global_file(out, value[1] ? &value[2] : NULL);
	}

	return git_buf_sets(out, value);
}