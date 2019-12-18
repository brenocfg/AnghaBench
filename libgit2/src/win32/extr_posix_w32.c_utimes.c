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
struct p_timeval {int dummy; } ;
struct open_opts {int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  git_win32_path ;
typedef  int DWORD ;

/* Variables and functions */
 int FILE_ATTRIBUTE_READONLY ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int GetFileAttributesW (int /*<<< orphan*/ ) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  O_RDWR ; 
 int /*<<< orphan*/  SetFileAttributesW (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 int open_once (int /*<<< orphan*/ ,struct open_opts*) ; 
 int /*<<< orphan*/  open_opts_from_posix (struct open_opts*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int p_futimes (int,struct p_timeval const*) ; 

int p_utimes(const char *path, const struct p_timeval times[2])
{
	git_win32_path wpath;
	int fd, error;
	DWORD attrs_orig, attrs_new = 0;
	struct open_opts opts = { 0 };

	if (git_win32_path_from_utf8(wpath, path) < 0)
		return -1;

	attrs_orig = GetFileAttributesW(wpath);

	if (attrs_orig & FILE_ATTRIBUTE_READONLY) {
		attrs_new = attrs_orig & ~FILE_ATTRIBUTE_READONLY;

		if (!SetFileAttributesW(wpath, attrs_new)) {
			git_error_set(GIT_ERROR_OS, "failed to set attributes");
			return -1;
		}
	}

	open_opts_from_posix(&opts, O_RDWR, 0);

	if ((fd = open_once(wpath, &opts)) < 0) {
		error = -1;
		goto done;
	}

	error = p_futimes(fd, times);
	close(fd);

done:
	if (attrs_orig != attrs_new) {
		DWORD os_error = GetLastError();
		SetFileAttributesW(wpath, attrs_orig);
		SetLastError(os_error);
	}

	return error;
}