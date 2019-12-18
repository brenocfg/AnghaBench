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
typedef  int uint32_t ;

/* Variables and functions */
 int CAP_FCNTL_ALL ; 
 int CAP_FCNTL_GETFL ; 
 int CAP_FCNTL_SETFL ; 
 int /*<<< orphan*/  CHECK (int) ; 
 scalar_t__ ENOTCAPABLE ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFD ; 
 int /*<<< orphan*/  F_SETFL ; 
 int O_NONBLOCK ; 
 int O_RDWR ; 
 scalar_t__ cap_fcntls_get (int,int*) ; 
 int cap_fcntls_limit (int,int) ; 
 scalar_t__ close (int) ; 
 scalar_t__ descriptor_recv (int,int*) ; 
 scalar_t__ errno ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
fcntl_tests_recv_0(int sock)
{
	uint32_t fcntlrights;
	int fd;

	CHECK(descriptor_recv(sock, &fd) == 0);

	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == CAP_FCNTL_ALL);

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(fcntl(fd, F_SETFD, FD_CLOEXEC) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(fcntl(fd, F_SETFD, 0) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	CHECK(fcntl(fd, F_GETFL) == O_RDWR);
	CHECK(fcntl(fd, F_SETFL, O_NONBLOCK) == 0);
	CHECK(fcntl(fd, F_GETFL) == (O_RDWR | O_NONBLOCK));
	CHECK(fcntl(fd, F_SETFL, 0) == 0);
	CHECK(fcntl(fd, F_GETFL) == O_RDWR);

	CHECK(close(fd) == 0);

	CHECK(descriptor_recv(sock, &fd) == 0);

	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == (CAP_FCNTL_GETFL | CAP_FCNTL_SETFL));
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL | CAP_FCNTL_SETFL) == 0);
	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == (CAP_FCNTL_GETFL | CAP_FCNTL_SETFL));

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(fcntl(fd, F_SETFD, FD_CLOEXEC) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(fcntl(fd, F_SETFD, 0) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	CHECK(fcntl(fd, F_GETFL) == O_RDWR);
	CHECK(fcntl(fd, F_SETFL, O_NONBLOCK) == 0);
	CHECK(fcntl(fd, F_GETFL) == (O_RDWR | O_NONBLOCK));
	CHECK(fcntl(fd, F_SETFL, 0) == 0);
	CHECK(fcntl(fd, F_GETFL) == O_RDWR);

	CHECK(close(fd) == 0);

	CHECK(descriptor_recv(sock, &fd) == 0);

	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == CAP_FCNTL_GETFL);
	errno = 0;
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL | CAP_FCNTL_SETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == CAP_FCNTL_GETFL);
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL) == 0);
	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == CAP_FCNTL_GETFL);

	CHECK(fcntl(fd, F_GETFD) == 0);
	CHECK(fcntl(fd, F_SETFD, FD_CLOEXEC) == 0);
	CHECK(fcntl(fd, F_GETFD) == FD_CLOEXEC);
	CHECK(fcntl(fd, F_SETFD, 0) == 0);
	CHECK(fcntl(fd, F_GETFD) == 0);

	CHECK(fcntl(fd, F_GETFL) == O_RDWR);
	errno = 0;
	CHECK(fcntl(fd, F_SETFL, O_NONBLOCK) == -1);
	CHECK(errno == ENOTCAPABLE);
	CHECK(fcntl(fd, F_GETFL) == O_RDWR);
	errno = 0;
	CHECK(fcntl(fd, F_SETFL, 0) == -1);
	CHECK(errno == ENOTCAPABLE);
	CHECK(fcntl(fd, F_GETFL) == O_RDWR);

	CHECK(close(fd) == 0);

	CHECK(descriptor_recv(sock, &fd) == 0);

	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == 0);
	errno = 0;
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL | CAP_FCNTL_SETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == 0);
	errno = 0;
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	fcntlrights = 0;
	CHECK(cap_fcntls_get(fd, &fcntlrights) == 0);
	CHECK(fcntlrights == 0);
	errno = 0;
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_SETFL) == -1);
	CHECK(errno == ENOTCAPABLE);
	fcntlrights = 0;
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

	CHECK(close(fd) == 0);
}