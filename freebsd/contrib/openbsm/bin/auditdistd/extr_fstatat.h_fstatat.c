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
 int AT_SYMLINK_NOFOLLOW ; 
 int O_DIRECTORY ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int fchdir (int) ; 
 int lstat (char const*,struct stat*) ; 
 int open (char*,int) ; 
 int stat (char const*,struct stat*) ; 

__attribute__((used)) static int
fstatat(int fd, const char *path, struct stat *buf, int flag)
{
	int cfd, error, ret;

	cfd = open(".", O_RDONLY | O_DIRECTORY);
	if (cfd == -1)
		return (-1);

	if (fchdir(fd) == -1) {
		error = errno;
		(void)close(cfd);
		errno = error;
		return (-1);
	}

	if (flag == AT_SYMLINK_NOFOLLOW)
		ret = lstat(path, buf);
	else
		ret = stat(path, buf);

	error = errno;
	(void)fchdir(cfd);
	(void)close(cfd);
	errno = error;
	return (ret);
}