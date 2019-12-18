#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
struct stat {int st_mode; int /*<<< orphan*/  st_size; } ;
typedef  int /*<<< orphan*/  git_win32_path ;
struct TYPE_3__ {int dwFileAttributes; int /*<<< orphan*/  ftLastWriteTime; int /*<<< orphan*/  ftLastAccessTime; int /*<<< orphan*/  ftCreationTime; int /*<<< orphan*/  nFileSizeLow; int /*<<< orphan*/  nFileSizeHigh; } ;
typedef  TYPE_1__ WIN32_FILE_ATTRIBUTE_DATA ;

/* Variables and functions */
 int FILE_ATTRIBUTE_REPARSE_POINT ; 
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int S_IFLNK ; 
 int S_IFMT ; 
 int /*<<< orphan*/  git__utf16_to_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  git_win32__stat_init (struct stat*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ git_win32_path_readlink_w (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int git_win32__file_attribute_to_stat(
	struct stat *st,
	const WIN32_FILE_ATTRIBUTE_DATA *attrdata,
	const wchar_t *path)
{
	git_win32__stat_init(st,
		attrdata->dwFileAttributes,
		attrdata->nFileSizeHigh,
		attrdata->nFileSizeLow,
		attrdata->ftCreationTime,
		attrdata->ftLastAccessTime,
		attrdata->ftLastWriteTime);

	if (attrdata->dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT && path) {
		git_win32_path target;

		if (git_win32_path_readlink_w(target, path) >= 0) {
			st->st_mode = (st->st_mode & ~S_IFMT) | S_IFLNK;

			/* st_size gets the UTF-8 length of the target name, in bytes,
			 * not counting the NULL terminator */
			if ((st->st_size = git__utf16_to_8(NULL, 0, target)) < 0) {
				git_error_set(GIT_ERROR_OS, "could not convert reparse point name for '%ls'", path);
				return -1;
			}
		}
	}

	return 0;
}