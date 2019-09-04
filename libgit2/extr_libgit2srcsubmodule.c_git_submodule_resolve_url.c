#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  git_repository ;
struct TYPE_10__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 TYPE_1__ GIT_BUF_INIT ; 
 int /*<<< orphan*/  GIT_ERROR_SUBMODULE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int get_url_base (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  git_buf_dispose (TYPE_1__*) ; 
 int /*<<< orphan*/  git_buf_sanitize (TYPE_1__*) ; 
 int git_buf_sets (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int git_path_apply_relative (TYPE_1__*,char const*) ; 
 scalar_t__ git_path_is_relative (char const*) ; 
 int git_path_normalize_slashes (TYPE_1__*,char const*) ; 
 int /*<<< orphan*/ * strchr (char const*,char) ; 

int git_submodule_resolve_url(git_buf *out, git_repository *repo, const char *url)
{
	int error = 0;
	git_buf normalized = GIT_BUF_INIT;

	assert(out && repo && url);

	git_buf_sanitize(out);

	/* We do this in all platforms in case someone on Windows created the .gitmodules */
	if (strchr(url, '\\')) {
		if ((error = git_path_normalize_slashes(&normalized, url)) < 0)
			return error;

		url = normalized.ptr;
	}


	if (git_path_is_relative(url)) {
		if (!(error = get_url_base(out, repo)))
			error = git_path_apply_relative(out, url);
	} else if (strchr(url, ':') != NULL || url[0] == '/') {
		error = git_buf_sets(out, url);
	} else {
		git_error_set(GIT_ERROR_SUBMODULE, "invalid format for submodule URL");
		error = -1;
	}

	git_buf_dispose(&normalized);
	return error;
}