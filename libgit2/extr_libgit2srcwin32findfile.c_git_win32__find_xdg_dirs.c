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
typedef  char wchar_t ;
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int win32_find_existing_dirs (int /*<<< orphan*/ *,char const**) ; 

int git_win32__find_xdg_dirs(git_buf *out)
{
	static const wchar_t *global_tmpls[7] = {
		L"%XDG_CONFIG_HOME%\\git",
		L"%APPDATA%\\git",
		L"%LOCALAPPDATA%\\git",
		L"%HOME%\\.config\\git",
		L"%HOMEDRIVE%%HOMEPATH%\\.config\\git",
		L"%USERPROFILE%\\.config\\git",
		NULL,
	};

	return win32_find_existing_dirs(out, global_tmpls);
}