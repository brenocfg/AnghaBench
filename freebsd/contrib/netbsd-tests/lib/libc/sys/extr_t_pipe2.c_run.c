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
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int /*<<< orphan*/  ATF_REQUIRE_MSG (int,char*,int /*<<< orphan*/ ) ; 
 int FD_CLOEXEC ; 
 int /*<<< orphan*/  F_GETFD ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_GETNOSIGPIPE ; 
 int O_CLOEXEC ; 
 int O_NONBLOCK ; 
 int O_NOSIGPIPE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int close (int) ; 
 int closefrom (int) ; 
 int /*<<< orphan*/  errno ; 
 int fcntl (int,int /*<<< orphan*/ ) ; 
 int open (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ pipe2 (int*,int) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
run(int flags)
{
	int fd[2], i;

	while ((i = open("/", O_RDONLY)) < 3)
		ATF_REQUIRE(i != -1);

#ifdef __FreeBSD__
	closefrom(3);
#else
	ATF_REQUIRE_MSG(closefrom(3) != -1, "closefrom failed: %s",
	    strerror(errno));
#endif

	ATF_REQUIRE(pipe2(fd, flags) == 0);

	ATF_REQUIRE(fd[0] == 3);
	ATF_REQUIRE(fd[1] == 4);

	if (flags & O_CLOEXEC) {
		ATF_REQUIRE((fcntl(fd[0], F_GETFD) & FD_CLOEXEC) != 0);
		ATF_REQUIRE((fcntl(fd[1], F_GETFD) & FD_CLOEXEC) != 0);
	} else {
		ATF_REQUIRE((fcntl(fd[0], F_GETFD) & FD_CLOEXEC) == 0);
		ATF_REQUIRE((fcntl(fd[1], F_GETFD) & FD_CLOEXEC) == 0);
	}

	if (flags & O_NONBLOCK) {
		ATF_REQUIRE((fcntl(fd[0], F_GETFL) & O_NONBLOCK) != 0);
		ATF_REQUIRE((fcntl(fd[1], F_GETFL) & O_NONBLOCK) != 0);
	} else {
		ATF_REQUIRE((fcntl(fd[0], F_GETFL) & O_NONBLOCK) == 0);
		ATF_REQUIRE((fcntl(fd[1], F_GETFL) & O_NONBLOCK) == 0);
	}

#ifndef __FreeBSD__
	if (flags & O_NOSIGPIPE) {
		ATF_REQUIRE(fcntl(fd[0], F_GETNOSIGPIPE) != 0);
		ATF_REQUIRE(fcntl(fd[1], F_GETNOSIGPIPE) != 0);
	} else {
		ATF_REQUIRE(fcntl(fd[0], F_GETNOSIGPIPE) == 0);
		ATF_REQUIRE(fcntl(fd[1], F_GETNOSIGPIPE) == 0);
	}
#endif

	ATF_REQUIRE(close(fd[0]) != -1);
	ATF_REQUIRE(close(fd[1]) != -1);
}