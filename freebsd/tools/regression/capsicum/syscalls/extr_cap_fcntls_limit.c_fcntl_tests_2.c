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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cap_rights_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_ALL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CAP_FCNTL ; 
 scalar_t__ CAP_FCNTL_ALL ; 
 int CAP_FCNTL_GETFL ; 
 int CAP_FCNTL_SETFL ; 
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ ENOTCAPABLE ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 scalar_t__ cap_fcntls_get (int,scalar_t__*) ; 
 int cap_fcntls_limit (int,int) ; 
 int /*<<< orphan*/  cap_rights_clear (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ cap_rights_limit (int,int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
fcntl_tests_2(int fd)
{
	uint32_t fcntlrights;
	cap_rights_t rights;

	CAP_ALL(&rights);
	cap_rights_clear(&rights, CAP_FCNTL);
	CHECK(cap_rights_limit(fd, &rights) == 0);

	fcntlrights = CAP_FCNTL_ALL;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == 0);

	errno = 0;
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL | CAP_FCNTL_SETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	fcntlrights = CAP_FCNTL_ALL;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == 0);
	errno = 0;
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	fcntlrights = CAP_FCNTL_ALL;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == 0);

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(fcntl(fd, F_SETFD, FD_CLOEXEC) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(fcntl(fd, F_SETFD, 0) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	errno = 0;
	CHECK(fcntl(fd, F_GETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	errno = 0;
	CHECK(fcntl(fd, F_SETFL, O_NONBLOCK) == -1);
	CHECK(errno == ENOTCAPABLE);
	errno = 0;
	CHECK(fcntl(fd, F_SETFL, 0) == -1);
	CHECK(errno == ENOTCAPABLE);
	errno = 0;
	CHECK(fcntl(fd, F_GETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
}