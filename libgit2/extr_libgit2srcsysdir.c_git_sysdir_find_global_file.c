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
typedef  int /*<<< orphan*/  git_buf ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_SYSDIR_GLOBAL ; 
 int git_sysdir_find_in_dirlist (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char*) ; 

int git_sysdir_find_global_file(git_buf *path, const char *filename)
{
	return git_sysdir_find_in_dirlist(
		path, filename, GIT_SYSDIR_GLOBAL, "global");
}