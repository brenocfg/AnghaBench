#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char* ptr; } ;
typedef  TYPE_1__ git_buf ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
 int GIT_ENOTFOUND ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GIT_PATH_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  git_buf_clear (TYPE_1__*) ; 
 scalar_t__ git_buf_joinpath (TYPE_1__*,char const*,char const*) ; 
 int git_buf_sets (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ git_path_root (char const*) ; 
 int /*<<< orphan*/ * p_realpath (char const*,char*) ; 

int git_path_prettify(git_buf *path_out, const char *path, const char *base)
{
	char buf[GIT_PATH_MAX];

	assert(path && path_out);

	/* construct path if needed */
	if (base != NULL && git_path_root(path) < 0) {
		if (git_buf_joinpath(path_out, base, path) < 0)
			return -1;
		path = path_out->ptr;
	}

	if (p_realpath(path, buf) == NULL) {
		/* git_error_set resets the errno when dealing with a GIT_ERROR_OS kind of error */
		int error = (errno == ENOENT || errno == ENOTDIR) ? GIT_ENOTFOUND : -1;
		git_error_set(GIT_ERROR_OS, "failed to resolve path '%s'", path);

		git_buf_clear(path_out);

		return error;
	}

	return git_buf_sets(path_out, buf);
}