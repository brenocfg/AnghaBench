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
 int /*<<< orphan*/  GIT_ERROR_INVALID ; 
 int INT_MAX ; 
 scalar_t__ git_buf_putc (int /*<<< orphan*/ *,char) ; 
 scalar_t__ git_buf_set (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 int strlen (char const*) ; 
 int win32_prefix_length (char const*,int) ; 

int git_path_dirname_r(git_buf *buffer, const char *path)
{
	const char *endp;
	int is_prefix = 0, len;

	/* Empty or NULL string gets treated as "." */
	if (path == NULL || *path == '\0') {
		path = ".";
		len = 1;
		goto Exit;
	}

	/* Strip trailing slashes */
	endp = path + strlen(path) - 1;
	while (endp > path && *endp == '/')
		endp--;

	if (endp - path + 1 > INT_MAX) {
		git_error_set(GIT_ERROR_INVALID, "path too long");
		len = -1;
		goto Exit;
	}

	if ((len = win32_prefix_length(path, (int)(endp - path + 1))) > 0) {
		is_prefix = 1;
		goto Exit;
	}

	/* Find the start of the dir */
	while (endp > path && *endp != '/')
		endp--;

	/* Either the dir is "/" or there are no slashes */
	if (endp == path) {
		path = (*endp == '/') ? "/" : ".";
		len = 1;
		goto Exit;
	}

	do {
		endp--;
	} while (endp > path && *endp == '/');

	if (endp - path + 1 > INT_MAX) {
		git_error_set(GIT_ERROR_INVALID, "path too long");
		len = -1;
		goto Exit;
	}

	if ((len = win32_prefix_length(path, (int)(endp - path + 1))) > 0) {
		is_prefix = 1;
		goto Exit;
	}

	/* Cast is safe because max path < max int */
	len = (int)(endp - path + 1);

Exit:
	if (buffer) {
		if (git_buf_set(buffer, path, len) < 0)
			return -1;
		if (is_prefix && git_buf_putc(buffer, '/') < 0)
			return -1;
	}

	return len;
}