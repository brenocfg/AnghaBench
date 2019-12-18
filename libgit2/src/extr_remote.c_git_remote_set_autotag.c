#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
typedef  int git_remote_autotag_option_t ;
typedef  int /*<<< orphan*/  git_config ;
struct TYPE_5__ {int /*<<< orphan*/  ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  CONFIG_TAGOPT_FMT ; 
 TYPE_1__ GIT_BUF_INIT ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
#define  GIT_REMOTE_DOWNLOAD_TAGS_ALL 130 
#define  GIT_REMOTE_DOWNLOAD_TAGS_AUTO 129 
#define  GIT_REMOTE_DOWNLOAD_TAGS_NONE 128 
 int /*<<< orphan*/  assert (int) ; 
 int ensure_remote_name_is_valid (char const*) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int git_buf_printf (TYPE_1__*,int /*<<< orphan*/ ,char const*) ; 
 int git_config_delete_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int git_config_set_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_repository_config__weakptr (int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

int git_remote_set_autotag(git_repository *repo, const char *remote, git_remote_autotag_option_t value)
{
	git_buf var = GIT_BUF_INIT;
	git_config *config;
	int error;

	assert(repo && remote);

	if ((error = ensure_remote_name_is_valid(remote)) < 0)
		return error;

	if ((error = git_repository_config__weakptr(&config, repo)) < 0)
		return error;

	if ((error = git_buf_printf(&var, CONFIG_TAGOPT_FMT, remote)))
		return error;

	switch (value) {
	case GIT_REMOTE_DOWNLOAD_TAGS_NONE:
		error = git_config_set_string(config, var.ptr, "--no-tags");
		break;
	case GIT_REMOTE_DOWNLOAD_TAGS_ALL:
		error = git_config_set_string(config, var.ptr, "--tags");
		break;
	case GIT_REMOTE_DOWNLOAD_TAGS_AUTO:
		error = git_config_delete_entry(config, var.ptr);
		if (error == GIT_ENOTFOUND)
			error = 0;
		break;
	default:
		git_error_set(GIT_ERROR_INVALID, "invalid value for the tagopt setting");
		error = -1;
	}

	git_buf_dispose(&var);
	return error;
}