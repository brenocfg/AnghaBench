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
 int /*<<< orphan*/  GIT_CONFIG_FILENAME_GLOBAL ; 
 int /*<<< orphan*/  git_buf_sanitize (int /*<<< orphan*/ *) ; 
 int git_sysdir_find_global_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int git_config_find_global(git_buf *path)
{
	git_buf_sanitize(path);
	return git_sysdir_find_global_file(path, GIT_CONFIG_FILENAME_GLOBAL);
}