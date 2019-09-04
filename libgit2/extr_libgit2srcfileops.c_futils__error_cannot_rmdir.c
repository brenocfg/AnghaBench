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

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*,...) ; 

__attribute__((used)) static int futils__error_cannot_rmdir(const char *path, const char *filemsg)
{
	if (filemsg)
		git_error_set(GIT_ERROR_OS, "could not remove directory '%s': %s",
				   path, filemsg);
	else
		git_error_set(GIT_ERROR_OS, "could not remove directory '%s'", path);

	return -1;
}