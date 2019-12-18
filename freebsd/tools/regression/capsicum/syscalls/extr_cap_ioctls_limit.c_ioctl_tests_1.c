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
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_ALL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CAP_IOCTL ; 
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ ENOTCAPABLE ; 
 scalar_t__ FD_CLOEXEC ; 
 unsigned long FIOCLEX ; 
 unsigned long FIONCLEX ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_SETFD ; 
 int cap_ioctls_get (int,unsigned long*,int) ; 
 int cap_ioctls_limit (int,unsigned long*,int) ; 
 int /*<<< orphan*/  cap_rights_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cap_rights_limit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,...) ; 
 int ioctl (int,unsigned long) ; 
 int nitems (unsigned long*) ; 

__attribute__((used)) static void
ioctl_tests_1(int fd)
{
	unsigned long cmds[2];
	cap_rights_t rights;

	cmds[0] = FIOCLEX;
	CHECK(cap_ioctls_limit(fd, cmds, 1) == 0);
	cmds[0] = cmds[1] = 0;
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == 1);
	CHECK(cmds[0] == FIOCLEX);
	CHECK(cmds[1] == 0);

	CAP_ALL(&rights);
	cap_rights_clear(&rights, CAP_IOCTL);

	CHECK(cap_rights_limit(fd, &rights) == 0);
	CHECK(cap_ioctls_get(fd, cmds, nitems(cmds)) == 0);

	cmds[0] = FIOCLEX;
	cmds[1] = FIONCLEX;
	errno = 0;
	CHECK(cap_ioctls_limit(fd, cmds, nitems(cmds)) == -1);
	CHECK(errno == ENOTCAPABLE);
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