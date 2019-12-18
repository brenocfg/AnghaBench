#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  int /*<<< orphan*/  git_win32_path ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_6__ {int SubstituteNameOffset; int SubstituteNameLength; int /*<<< orphan*/  PathBuffer; } ;
struct TYPE_5__ {int SubstituteNameOffset; int SubstituteNameLength; int /*<<< orphan*/  PathBuffer; } ;
struct TYPE_7__ {int ReparseTag; TYPE_2__ MountPointReparseBuffer; TYPE_1__ SymbolicLinkReparseBuffer; } ;
typedef  scalar_t__ HANDLE ;
typedef  TYPE_3__ GIT_REPARSE_DATA_BUFFER ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateFileW (int /*<<< orphan*/  const,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeviceIoControl (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOENT ; 
 int FILE_FLAG_BACKUP_SEMANTICS ; 
 int FILE_FLAG_OPEN_REPARSE_POINT ; 
 int FILE_SHARE_DELETE ; 
 int FILE_SHARE_READ ; 
 int /*<<< orphan*/  FSCTL_GET_REPARSE_POINT ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 size_t GIT_WIN_PATH_UTF16 ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
#define  IO_REPARSE_TAG_MOUNT_POINT 129 
#define  IO_REPARSE_TAG_SYMLINK 128 
 int MAXIMUM_REPARSE_DATA_BUFFER_SIZE ; 
 int /*<<< orphan*/  OPEN_EXISTING ; 
 int /*<<< orphan*/  errno ; 
 size_t git_win32_path_remove_namespace (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ path_is_volume (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  wcscpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int git_win32_path_readlink_w(git_win32_path dest, const git_win32_path path)
{
	BYTE buf[MAXIMUM_REPARSE_DATA_BUFFER_SIZE];
	GIT_REPARSE_DATA_BUFFER *reparse_buf = (GIT_REPARSE_DATA_BUFFER *)buf;
	HANDLE handle = NULL;
	DWORD ioctl_ret;
	wchar_t *target;
	size_t target_len;

	int error = -1;

	handle = CreateFileW(path, GENERIC_READ,
		FILE_SHARE_READ | FILE_SHARE_DELETE, NULL, OPEN_EXISTING,
		FILE_FLAG_OPEN_REPARSE_POINT | FILE_FLAG_BACKUP_SEMANTICS, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		errno = ENOENT;
		return -1;
	}

	if (!DeviceIoControl(handle, FSCTL_GET_REPARSE_POINT, NULL, 0,
		reparse_buf, sizeof(buf), &ioctl_ret, NULL)) {
		errno = EINVAL;
		goto on_error;
	}

	switch (reparse_buf->ReparseTag) {
	case IO_REPARSE_TAG_SYMLINK:
		target = reparse_buf->SymbolicLinkReparseBuffer.PathBuffer +
			(reparse_buf->SymbolicLinkReparseBuffer.SubstituteNameOffset / sizeof(WCHAR));
		target_len = reparse_buf->SymbolicLinkReparseBuffer.SubstituteNameLength / sizeof(WCHAR);
	break;
	case IO_REPARSE_TAG_MOUNT_POINT:
		target = reparse_buf->MountPointReparseBuffer.PathBuffer +
			(reparse_buf->MountPointReparseBuffer.SubstituteNameOffset / sizeof(WCHAR));
		target_len = reparse_buf->MountPointReparseBuffer.SubstituteNameLength / sizeof(WCHAR);
	break;
	default:
		errno = EINVAL;
		goto on_error;
	}

	if (path_is_volume(target, target_len)) {
		/* This path is a reparse point that represents another volume mounted
		 * at this location, it is not a symbolic link our input was canonical.
		 */
		errno = EINVAL;
		error = -1;
	} else if (target_len) {
		/* The path may need to have a namespace prefix removed. */
		target_len = git_win32_path_remove_namespace(target, target_len);

		/* Need one additional character in the target buffer
		 * for the terminating NULL. */
		if (GIT_WIN_PATH_UTF16 > target_len) {
			wcscpy(dest, target);
			error = (int)target_len;
		}
	}

on_error:
	CloseHandle(handle);
	return error;
}