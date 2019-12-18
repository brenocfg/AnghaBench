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
struct stat {int dummy; } ;
typedef  int /*<<< orphan*/  git_win32_path ;

/* Variables and functions */
 int git_win32_path_from_utf8 (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  git_win32_path_trim_end (int /*<<< orphan*/ ,int) ; 
 int lstat_w (int /*<<< orphan*/ ,struct stat*,int) ; 

__attribute__((used)) static int do_lstat(const char *path, struct stat *buf, bool posixly_correct)
{
	git_win32_path path_w;
	int len;

	if ((len = git_win32_path_from_utf8(path_w, path)) < 0)
		return -1;

	git_win32_path_trim_end(path_w, len);

	return lstat_w(path_w, buf, posixly_correct);
}