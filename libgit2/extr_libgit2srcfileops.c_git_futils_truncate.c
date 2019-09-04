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
 int O_CLOEXEC ; 
 int O_CREAT ; 
 int O_TRUNC ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  errno ; 
 int git_path_set_error (int /*<<< orphan*/ ,char const*,char*) ; 
 int p_open (char const*,int,int) ; 

int git_futils_truncate(const char *path, int mode)
{
	int fd = p_open(path, O_WRONLY | O_CREAT | O_TRUNC | O_CLOEXEC, mode);
	if (fd < 0)
		return git_path_set_error(errno, path, "open");

	close(fd);
	return 0;
}