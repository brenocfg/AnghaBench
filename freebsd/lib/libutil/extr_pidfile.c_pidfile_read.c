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
typedef  int /*<<< orphan*/  pid_t ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  close (int) ; 
 int errno ; 
 int openat (int,char const*,int) ; 
 int read (int,char*,int) ; 
 int /*<<< orphan*/  strtol (char*,char**,int) ; 

__attribute__((used)) static int
pidfile_read(int dirfd, const char *filename, pid_t *pidptr)
{
	char buf[16], *endptr;
	int error, fd, i;

	fd = openat(dirfd, filename, O_RDONLY | O_CLOEXEC);
	if (fd == -1)
		return (errno);

	i = read(fd, buf, sizeof(buf) - 1);
	error = errno;	/* Remember errno in case close() wants to change it. */
	close(fd);
	if (i == -1)
		return (error);
	else if (i == 0)
		return (EAGAIN);
	buf[i] = '\0';

	*pidptr = strtol(buf, &endptr, 10);
	if (endptr != &buf[i])
		return (EINVAL);

	return (0);
}