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
typedef  int /*<<< orphan*/  mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  GIT_ERROR_OS ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 scalar_t__ p_close (int) ; 
 int p_creat (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int create_empty_file(const char *path, mode_t mode)
{
	int fd;

	if ((fd = p_creat(path, mode)) < 0) {
		git_error_set(GIT_ERROR_OS, "error while creating '%s'", path);
		return -1;
	}

	if (p_close(fd) < 0) {
		git_error_set(GIT_ERROR_OS, "error while closing '%s'", path);
		return -1;
	}

	return 0;
}