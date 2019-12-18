#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  WIN32_FIND_DATAW ;
struct TYPE_4__ {int /*<<< orphan*/  dd_dir; scalar_t__ dd_stat; scalar_t__ dd_handle; } ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;
typedef  TYPE_1__ DIR ;

/* Variables and functions */
 int /*<<< orphan*/  ENOTDIR ; 
 scalar_t__ ERROR_DIRECTORY ; 
 scalar_t__ FindFirstFileW (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  MAX_PATH ; 
 int /*<<< orphan*/  err_win_to_posix (scalar_t__) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  finddata2dirent (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_dir_sep (char) ; 
 TYPE_1__* xmalloc (int) ; 
 int xutftowcs_path (char*,char const*) ; 

DIR *opendir(const char *name)
{
	wchar_t pattern[MAX_PATH + 2]; /* + 2 for '/' '*' */
	WIN32_FIND_DATAW fdata;
	HANDLE h;
	int len;
	DIR *dir;

	/* convert name to UTF-16 and check length < MAX_PATH */
	if ((len = xutftowcs_path(pattern, name)) < 0)
		return NULL;

	/* append optional '/' and wildcard '*' */
	if (len && !is_dir_sep(pattern[len - 1]))
		pattern[len++] = '/';
	pattern[len++] = '*';
	pattern[len] = 0;

	/* open find handle */
	h = FindFirstFileW(pattern, &fdata);
	if (h == INVALID_HANDLE_VALUE) {
		DWORD err = GetLastError();
		errno = (err == ERROR_DIRECTORY) ? ENOTDIR : err_win_to_posix(err);
		return NULL;
	}

	/* initialize DIR structure and copy first dir entry */
	dir = xmalloc(sizeof(DIR));
	dir->dd_handle = h;
	dir->dd_stat = 0;
	finddata2dirent(&dir->dd_dir, &fdata);
	return dir;
}