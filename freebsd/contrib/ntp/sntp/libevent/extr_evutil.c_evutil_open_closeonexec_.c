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
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  FD_CLOEXEC ; 
 int /*<<< orphan*/  F_SETFD ; 
 int O_CLOEXEC ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int open (char const*,int,int /*<<< orphan*/ ) ; 

int
evutil_open_closeonexec_(const char *pathname, int flags, unsigned mode)
{
	int fd;

#ifdef O_CLOEXEC
	fd = open(pathname, flags|O_CLOEXEC, (mode_t)mode);
	if (fd >= 0 || errno == EINVAL)
		return fd;
	/* If we got an EINVAL, fall through and try without O_CLOEXEC */
#endif
	fd = open(pathname, flags, (mode_t)mode);
	if (fd < 0)
		return -1;

#if defined(FD_CLOEXEC)
	if (fcntl(fd, F_SETFD, FD_CLOEXEC) < 0) {
		close(fd);
		return -1;
	}
#endif

	return fd;
}