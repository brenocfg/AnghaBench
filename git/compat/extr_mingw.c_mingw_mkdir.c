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
 int MAX_PATH ; 
 int _wmkdir (int /*<<< orphan*/ *) ; 
 scalar_t__ needs_hiding (char const*) ; 
 int set_hidden_flag (int /*<<< orphan*/ *,int) ; 
 scalar_t__ xutftowcs_path (int /*<<< orphan*/ *,char const*) ; 

int mingw_mkdir(const char *path, int mode)
{
	int ret;
	wchar_t wpath[MAX_PATH];
	if (xutftowcs_path(wpath, path) < 0)
		return -1;
	ret = _wmkdir(wpath);
	if (!ret && needs_hiding(path))
		return set_hidden_flag(wpath, 1);
	return ret;
}