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
struct pidfh {int pf_fd; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  pidstr ;

/* Variables and functions */
 int /*<<< orphan*/  _pidfile_remove (struct pidfh*,int /*<<< orphan*/ ) ; 
 int errno ; 
 int ftruncate (int,int /*<<< orphan*/ ) ; 
 int getpid () ; 
 int pidfile_verify (struct pidfh*) ; 
 scalar_t__ pwrite (int,char*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 scalar_t__ strlen (char*) ; 

int
pidfile_write(struct pidfh *pfh)
{
	char pidstr[16];
	int error, fd;

	/*
	 * Check remembered descriptor, so we don't overwrite some other
	 * file if pidfile was closed and descriptor reused.
	 */
	errno = pidfile_verify(pfh);
	if (errno != 0) {
		/*
		 * Don't close descriptor, because we are not sure if it's ours.
		 */
		return (-1);
	}
	fd = pfh->pf_fd;

	/*
	 * Truncate PID file, so multiple calls of pidfile_write() are allowed.
	 */
	if (ftruncate(fd, 0) == -1) {
		error = errno;
		_pidfile_remove(pfh, 0);
		errno = error;
		return (-1);
	}

	snprintf(pidstr, sizeof(pidstr), "%u", getpid());
	if (pwrite(fd, pidstr, strlen(pidstr), 0) != (ssize_t)strlen(pidstr)) {
		error = errno;
		_pidfile_remove(pfh, 0);
		errno = error;
		return (-1);
	}

	return (0);
}