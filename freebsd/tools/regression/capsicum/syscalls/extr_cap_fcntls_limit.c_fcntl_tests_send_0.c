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
 int CAP_FCNTL_GETFL ; 
 int CAP_FCNTL_SETFL ; 
 int /*<<< orphan*/  CHECK (int) ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ cap_fcntls_limit (int,int) ; 
 scalar_t__ close (int) ; 
 scalar_t__ descriptor_send (int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
fcntl_tests_send_0(int sock)
{
	int fd;

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL | CAP_FCNTL_SETFL) == 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	CHECK(cap_fcntls_limit(fd, CAP_FCNTL_GETFL) == 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);

	CHECK((fd = socket(AF_UNIX, SOCK_STREAM, 0)) >= 0);
	CHECK(cap_fcntls_limit(fd, 0) == 0);
	CHECK(descriptor_send(sock, fd) == 0);
	CHECK(close(fd) == 0);
}