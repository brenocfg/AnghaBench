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
 int AT_EACCESS ; 
 int EINVAL ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int access (char const*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fchdir (int) ; 
 int open (char*,int) ; 

__attribute__((used)) static int
faccessat(int fd, const char *path, int mode, int flag)
{
	int cfd, error, ret;

	if (flag == AT_EACCESS) {
		errno = EINVAL;
		return (-1);
	}

	cfd = open(".", O_RDONLY | O_DIRECTORY);
	if (cfd == -1)
		return (-1);

	if (fchdir(fd) == -1) {
		error = errno;
		(void)close(cfd);
		errno = error;
		return (-1);
	}

	ret = access(path, mode);

	error = errno;
	(void)fchdir(cfd);
	(void)close(cfd);
	errno = error;
	return (ret);
}