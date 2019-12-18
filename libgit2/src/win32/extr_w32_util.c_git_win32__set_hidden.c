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
typedef  int DWORD ;

/* Variables and functions */
 int FILE_ATTRIBUTE_HIDDEN ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  SetFileAttributesW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char*,char const*) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 

int git_win32__set_hidden(const char *path, bool hidden)
{
	git_win32_path buf;
	DWORD attrs, newattrs;

	if (git_win32_path_from_utf8(buf, path) < 0)
		return -1;

	attrs = GetFileAttributesW(buf);

	/* Ensure the path exists */
	if (attrs == INVALID_FILE_ATTRIBUTES)
		return -1;

	if (hidden)
		newattrs = attrs | FILE_ATTRIBUTE_HIDDEN;
	else
		newattrs = attrs & ~FILE_ATTRIBUTE_HIDDEN;

	if (attrs != newattrs && !SetFileAttributesW(buf, newattrs)) {
		git_error_set(GIT_ERROR_OS, "failed to %s hidden bit for '%s'",
			hidden ? "set" : "unset", path);
		return -1;
	}

	return 0;
}