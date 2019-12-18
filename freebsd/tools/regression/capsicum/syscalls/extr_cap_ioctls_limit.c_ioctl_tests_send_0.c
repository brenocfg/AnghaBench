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
 int /*<<< orphan*/  AF_UNIX ; 
 int /*<<< orphan*/  CHECK (int) ; 
 unsigned long FIOCLEX ; 
 unsigned long FIONCLEX ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ cap_ioctls_limit (int,unsigned long*,int) ; 
 scalar_t__ close (int) ; 
 scalar_t__ descriptor_send (int,int) ; 
 int nitems (unsigned long*) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ioctl_tests_send_0(int sock)
{
	unsigned long cmds[2];
	int fd;

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	cmds[0] = FIOCLEX;
	cmds[1] = FIONCLEX;
	CHECK(cap_ioctls_limit(fd, cmds, nitems(cmds)) == 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	cmds[0] = FIOCLEX;
	CHECK(cap_ioctls_limit(fd, cmds, 1) == 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	CHECK(cap_ioctls_limit(fd, NULL, 0) == 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);
}