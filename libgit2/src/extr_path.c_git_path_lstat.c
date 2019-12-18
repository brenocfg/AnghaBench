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

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int git_path_set_error (int /*<<< orphan*/ ,char const*,char*) ; 
 scalar_t__ p_lstat (char const*,struct stat*) ; 

int git_path_lstat(const char *path, struct stat *st)
{
	if (p_lstat(path, st) == 0)
		return 0;

	return git_path_set_error(errno, path, "stat");
}