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
typedef  int wchar_t ;
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  WIN32_FILE_ATTRIBUTE_DATA ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ EACCES ; 
 scalar_t__ ENOENT ; 
 scalar_t__ ENOTDIR ; 
#define  ERROR_ACCESS_DENIED 128 
 int FILE_ATTRIBUTE_DIRECTORY ; 
 scalar_t__ GetFileAttributesExW (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int GetFileAttributesW (int*) ; 
 int /*<<< orphan*/  GetFileExInfoStandard ; 
 int GetLastError () ; 
 int INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  WIN32_IS_WSEP (int) ; 
 scalar_t__ errno ; 
 int git_win32__file_attribute_to_stat (struct stat*,int /*<<< orphan*/ *,int*) ; 
 size_t wcslen (int*) ; 

__attribute__((used)) static int lstat_w(
	wchar_t *path,
	struct stat *buf,
	bool posix_enotdir)
{
	WIN32_FILE_ATTRIBUTE_DATA fdata;

	if (GetFileAttributesExW(path, GetFileExInfoStandard, &fdata)) {
		if (!buf)
			return 0;

		return git_win32__file_attribute_to_stat(buf, &fdata, path);
	}

	switch (GetLastError()) {
	case ERROR_ACCESS_DENIED:
		errno = EACCES;
		break;
	default:
		errno = ENOENT;
		break;
	}

	/* To match POSIX behavior, set ENOTDIR when any of the folders in the
	 * file path is a regular file, otherwise set ENOENT.
	 */
	if (errno == ENOENT && posix_enotdir) {
		size_t path_len = wcslen(path);

		/* scan up path until we find an existing item */
		while (1) {
			DWORD attrs;

			/* remove last directory component */
			for (path_len--; path_len > 0 && !WIN32_IS_WSEP(path[path_len]); path_len--);

			if (path_len <= 0)
				break;

			path[path_len] = L'\0';
			attrs = GetFileAttributesW(path);

			if (attrs != INVALID_FILE_ATTRIBUTES) {
				if (!(attrs & FILE_ATTRIBUTE_DIRECTORY))
					errno = ENOTDIR;
				break;
			}
		}
	}

	return -1;
}