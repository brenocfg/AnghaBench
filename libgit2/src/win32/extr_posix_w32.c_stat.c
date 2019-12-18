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
struct stat {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 scalar_t__ S_ISLNK (int /*<<< orphan*/ ) ; 
 int follow_and_lstat_link (int /*<<< orphan*/ ,struct stat*) ; 
 int git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ lstat_w (int /*<<< orphan*/ ,struct stat*,int) ; 

int p_stat(const char* path, struct stat* buf)
{
	git_win32_path path_w;
	int len;

	if ((len = git_win32_path_from_utf8(path_w, path)) < 0 ||
		lstat_w(path_w, buf, false) < 0)
		return -1;

	/* The item is a symbolic link or mount point. No need to iterate
	 * to follow multiple links; use GetFinalPathNameFromHandle. */
	if (S_ISLNK(buf->st_mode))
		return follow_and_lstat_link(path_w, buf);

	return 0;
}