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
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int O_CREAT ; 
 int O_EXCL ; 
 int O_WRONLY ; 
 int close (int) ; 
 int /*<<< orphan*/  emergency (char*,char const*,...) ; 
 int /*<<< orphan*/  errno ; 
 int open (char const*,int,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,void const*,size_t) ; 

__attribute__((used)) static int
create_file(const char *path, const void *buf, size_t bufsize)
{
	ssize_t nbytes;
	int error, fd;

	fd = open(path, O_WRONLY | O_CREAT | O_EXCL, 0700);
	if (fd < 0) {
		emergency("%s: %s", path, strerror(errno));
		return (-1);
	}

	nbytes = write(fd, buf, bufsize);
	if (nbytes != (ssize_t)bufsize) {
		emergency("write: %s", strerror(errno));
		close(fd);
		return (-1);
	}

	error = close(fd);
	if (error != 0) {
		emergency("close: %s", strerror(errno));
		return (-1);
	}

	return (0);
}