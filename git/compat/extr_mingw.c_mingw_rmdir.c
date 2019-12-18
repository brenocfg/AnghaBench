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
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ EACCES ; 
 scalar_t__ ENOTEMPTY ; 
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 int _wrmdir (int /*<<< orphan*/ *) ; 
 scalar_t__ ask_yes_no_if_possible (char*,char const*) ; 
 int /*<<< orphan*/ * delay ; 
 scalar_t__ err_win_to_posix (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  is_dir_empty (int /*<<< orphan*/ *) ; 
 scalar_t__ is_file_in_use_error (int /*<<< orphan*/ ) ; 
 scalar_t__ xutftowcs_path (int /*<<< orphan*/ *,char const*) ; 

int mingw_rmdir(const char *pathname)
{
	int ret, tries = 0;
	wchar_t wpathname[MAX_PATH];
	if (xutftowcs_path(wpathname, pathname) < 0)
		return -1;

	while ((ret = _wrmdir(wpathname)) == -1 && tries < ARRAY_SIZE(delay)) {
		if (!is_file_in_use_error(GetLastError()))
			errno = err_win_to_posix(GetLastError());
		if (errno != EACCES)
			break;
		if (!is_dir_empty(wpathname)) {
			errno = ENOTEMPTY;
			break;
		}
		/*
		 * We assume that some other process had the source or
		 * destination file open at the wrong moment and retry.
		 * In order to give the other process a higher chance to
		 * complete its operation, we give up our time slice now.
		 * If we have to retry again, we do sleep a bit.
		 */
		Sleep(delay[tries]);
		tries++;
	}
	while (ret == -1 && errno == EACCES && is_file_in_use_error(GetLastError()) &&
	       ask_yes_no_if_possible("Deletion of directory '%s' failed. "
			"Should I try again?", pathname))
	       ret = _wrmdir(wpathname);
	return ret;
}