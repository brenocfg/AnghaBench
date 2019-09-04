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
 int /*<<< orphan*/  GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  Sleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _wchmod (int /*<<< orphan*/ *,int) ; 
 int _wunlink (int /*<<< orphan*/ *) ; 
 scalar_t__ ask_yes_no_if_possible (char*,char const*) ; 
 int /*<<< orphan*/ * delay ; 
 scalar_t__ is_file_in_use_error (int /*<<< orphan*/ ) ; 
 scalar_t__ xutftowcs_path (int /*<<< orphan*/ *,char const*) ; 

int mingw_unlink(const char *pathname)
{
	int ret, tries = 0;
	wchar_t wpathname[MAX_PATH];
	if (xutftowcs_path(wpathname, pathname) < 0)
		return -1;

	/* read-only files cannot be removed */
	_wchmod(wpathname, 0666);
	while ((ret = _wunlink(wpathname)) == -1 && tries < ARRAY_SIZE(delay)) {
		if (!is_file_in_use_error(GetLastError()))
			break;
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
	while (ret == -1 && is_file_in_use_error(GetLastError()) &&
	       ask_yes_no_if_possible("Unlink of file '%s' failed. "
			"Should I try again?", pathname))
	       ret = _wunlink(wpathname);
	return ret;
}