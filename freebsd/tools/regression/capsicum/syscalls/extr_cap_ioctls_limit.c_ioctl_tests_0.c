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
 int CAP_IOCTLS_ALL ; 
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ ENOTCAPABLE ; 
 scalar_t__ FD_CLOEXEC ; 
 unsigned long FIOCLEX ; 
 unsigned long FIONCLEX ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int cap_ioctls_get (int,unsigned long*,int) ; 
 int cap_ioctls_limit (int,unsigned long*,int) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,...) ; 
 int ioctl (int,unsigned long) ; 
 int nitems (unsigned long*) ; 

__attribute__((used)) static void
ioctl_tests_0(int fd)
{
	unsigned long cmds[2];

	CHECK(cap_ioctls_get(fd, NULL, 0) == CAP_IOCTLS_ALL);

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(ioctl(fd, FIOCLEX) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(ioctl(fd, FIONCLEX) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	cmds[0] = FIOCLEX;
	cmds[1] = FIONCLEX;
	CHECK(cap_ioctls_limit(fd, cmds, nitems(cmds)) == 0);
	cmds[0] = cmds[1] = 0;
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == nitems(cmds));
	CHECK((cmds[0] == FIOCLEX && cmds[1] == FIONCLEX) ||
	    (cmds[0] == FIONCLEX && cmds[1] == FIOCLEX));
	cmds[0] = FIOCLEX;
	cmds[1] = FIONCLEX;
	CHECK(cap_ioctls_limit(fd, cmds, nitems(cmds)) == 0);
	cmds[0] = cmds[1] = 0;
	CHECK(cap_ioctls_get(fd, cmds, 1) == nitems(cmds));
	CHECK(cmds[0] == FIOCLEX || cmds[0] == FIONCLEX);
	CHECK(cmds[1] == 0);

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(ioctl(fd, FIOCLEX) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(ioctl(fd, FIONCLEX) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	cmds[0] = FIOCLEX;
	CHECK(cap_ioctls_limit(fd, cmds, 1) == 0);
	cmds[0] = cmds[1] = 0;
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == 1);
	CHECK(cmds[0] == FIOCLEX);
	cmds[0] = FIOCLEX;
	cmds[1] = FIONCLEX;
	errno = 0;
	CHECK(cap_ioctls_limit(fd, cmds, nitems(cmds)) == -1);
	CHECK(errno == ENOTCAPABLE);
	cmds[0] = cmds[1] = 0;
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == 1);
	CHECK(cmds[0] == FIOCLEX);

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(ioctl(fd, FIOCLEX) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	errno = 0;
	CHECK(ioctl(fd, FIONCLEX) == -1);
	CHECK(errno == ENOTCAPABLE);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(fcntl(fd, F_SETFD, 0) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	CHECK(cap_ioctls_limit(fd, NULL, 0) == 0);
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == 0);
	cmds[0] = FIOCLEX;
	errno = 0;
	CHECK(cap_ioctls_limit(fd, cmds, 1) == -1);
	CHECK(errno == ENOTCAPABLE);
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == 0);

	CHECK(fcntl(fd, F_GETFD) == 0);
	errno = 0;
	CHECK(ioctl(fd, FIOCLEX) == -1);
	CHECK(errno == ENOTCAPABLE);
	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(fcntl(fd, F_SETFD, FD_CLOEXEC) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	errno = 0;
	CHECK(ioctl(fd, FIONCLEX) == -1);
	CHECK(errno == ENOTCAPABLE);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(fcntl(fd, F_SETFD, 0) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);
}