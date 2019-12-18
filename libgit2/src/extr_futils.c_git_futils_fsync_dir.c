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
 int /*<<< orphan*/  GIT_UNUSED (char const*) ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  git_error_set (int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  p_close (int) ; 
 int p_fsync (int) ; 
 int p_open (char const*,int /*<<< orphan*/ ) ; 

int git_futils_fsync_dir(const char *path)
{
#ifdef GIT_WIN32
	GIT_UNUSED(path);
	return 0;
#else
	int fd, error = -1;

	if ((fd = p_open(path, O_RDONLY)) < 0) {
		git_error_set(GIT_ERROR_OS, "failed to open directory '%s' for fsync", path);
		return -1;
	}

	if ((error = p_fsync(fd)) < 0)
		git_error_set(GIT_ERROR_OS, "failed to fsync directory '%s'", path);

	p_close(fd);
	return error;
#endif
}