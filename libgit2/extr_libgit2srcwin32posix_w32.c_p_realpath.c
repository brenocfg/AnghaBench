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
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int /*<<< orphan*/  ENOENT ; 
 int /*<<< orphan*/  ENOMEM ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 int /*<<< orphan*/  GIT_WIN_PATH_UTF16 ; 
 int /*<<< orphan*/  GIT_WIN_PATH_UTF8 ; 
 scalar_t__ GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetFullPathNameW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  errno ; 
 char* git__malloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_path_mkposix (char*) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ git_win32_path_to_utf8 (char*,int /*<<< orphan*/ ) ; 

char *p_realpath(const char *orig_path, char *buffer)
{
	git_win32_path orig_path_w, buffer_w;

	if (git_win32_path_from_utf8(orig_path_w, orig_path) < 0)
		return NULL;

	/* Note that if the path provided is a relative path, then the current directory
	 * is used to resolve the path -- which is a concurrency issue because the current
	 * directory is a process-wide variable. */
	if (!GetFullPathNameW(orig_path_w, GIT_WIN_PATH_UTF16, buffer_w, NULL)) {
		if (GetLastError() == ERROR_INSUFFICIENT_BUFFER)
			errno = ENAMETOOLONG;
		else
			errno = EINVAL;

		return NULL;
	}

	/* The path must exist. */
	if (GetFileAttributesW(buffer_w) == INVALID_FILE_ATTRIBUTES) {
		errno = ENOENT;
		return NULL;
	}

	if (!buffer && !(buffer = git__malloc(GIT_WIN_PATH_UTF8))) {
		errno = ENOMEM;
		return NULL;
	}

	/* Convert the path to UTF-8. If the caller provided a buffer, then it
	 * is assumed to be GIT_WIN_PATH_UTF8 characters in size. If it isn't,
	 * then we may overflow. */
	if (git_win32_path_to_utf8(buffer, buffer_w) < 0)
		return NULL;

	git_path_mkposix(buffer);

	return buffer;
}