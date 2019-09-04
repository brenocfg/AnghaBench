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
typedef  int /*<<< orphan*/  wchar_t ;

/* Variables and functions */
 int /*<<< orphan*/  CreateHardLinkW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  err_win_to_posix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ xutftowcs_path (int /*<<< orphan*/ *,char const*) ; 

int link(const char *oldpath, const char *newpath)
{
	wchar_t woldpath[MAX_PATH], wnewpath[MAX_PATH];
	if (xutftowcs_path(woldpath, oldpath) < 0 ||
		xutftowcs_path(wnewpath, newpath) < 0)
		return -1;

	if (!CreateHardLinkW(wnewpath, woldpath, NULL)) {
		errno = err_win_to_posix(GetLastError());
		return -1;
	}
	return 0;
}