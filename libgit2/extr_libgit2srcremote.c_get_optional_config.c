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
typedef  int /*<<< orphan*/ * git_config_foreach_cb ;
typedef  int /*<<< orphan*/  git_config ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int GIT_ENOTFOUND ; 
 char* git_buf_cstr (int /*<<< orphan*/ *) ; 
 scalar_t__ git_buf_oom (int /*<<< orphan*/ *) ; 
 int git_config_get_multivar_foreach (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ; 
 int git_config_get_string (void*,int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  git_error_clear () ; 

__attribute__((used)) static int get_optional_config(
	bool *found, git_config *config, git_buf *buf,
	git_config_foreach_cb cb, void *payload)
{
	int error = 0;
	const char *key = git_buf_cstr(buf);

	if (git_buf_oom(buf))
		return -1;

	if (cb != NULL)
		error = git_config_get_multivar_foreach(config, key, NULL, cb, payload);
	else
		error = git_config_get_string(payload, config, key);

	if (found)
		*found = !error;

	if (error == GIT_ENOTFOUND) {
		git_error_clear();
		error = 0;
	}

	return error;
}