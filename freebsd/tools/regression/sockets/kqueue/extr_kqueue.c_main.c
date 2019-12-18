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
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  OK (char*) ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_UNIX ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int close (int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fail (int /*<<< orphan*/ ,char*,char*,char*) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int kqueue () ; 
 int /*<<< orphan*/  printf (char*) ; 
 int socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  test_evfilt_read (int,int*,char*) ; 
 int /*<<< orphan*/  test_evfilt_write (int,int*,char*) ; 

int
main(void)
{
	int kq, sv[2];

	printf("1..49\n");

	kq = kqueue();
	if (kq == -1)
		fail(errno, "kqueue", NULL, NULL);
	OK("kqueue()");

	/*
	 * Create a UNIX domain datagram socket, and attach/test/detach a
	 * read filter on it.
	 */
	if (socketpair(PF_UNIX, SOCK_DGRAM, 0, sv) == -1)
		fail(errno, "socketpair", "PF_UNIX, SOCK_DGRAM", NULL);
	OK("socketpair() 1");

	if (fcntl(sv[0], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_DGRAM", "O_NONBLOCK");
	OK("fcntl() 1");
	if (fcntl(sv[1], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_DGRAM", "O_NONBLOCK");
	OK("fnctl() 2");

	test_evfilt_read(kq, sv, "PF_UNIX, SOCK_DGRAM");

	if (close(sv[0]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_DGRAM", "sv[0]");
	OK("close() 1");
	if (close(sv[1]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_DGRAM", "sv[1]");
	OK("close() 2");

#if 0
	/*
	 * XXXRW: We disable the write test in the case of datagram sockets,
	 * as kqueue can't tell when the remote socket receive buffer is
	 * full, whereas the UNIX domain socket implementation can tell and
	 * returns ENOBUFS.
	 */
	/*
	 * Create a UNIX domain datagram socket, and attach/test/detach a
	 * write filter on it.
	 */
	if (socketpair(PF_UNIX, SOCK_DGRAM, 0, sv) == -1)
		fail(errno, "socketpair", "PF_UNIX, SOCK_DGRAM", NULL);

	if (fcntl(sv[0], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_DGRAM", "O_NONBLOCK");
	if (fcntl(sv[1], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_DGRAM", "O_NONBLOCK");

	test_evfilt_write(kq, sv, "PF_UNIX, SOCK_DGRAM");

	if (close(sv[0]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_DGRAM", "sv[0]");
	if (close(sv[1]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_DGRAM", "sv[1]");
#endif

	/*
	 * Create a UNIX domain stream socket, and attach/test/detach a
	 * read filter on it.
	 */
	if (socketpair(PF_UNIX, SOCK_STREAM, 0, sv) == -1)
		fail(errno, "socketpair", "PF_UNIX, SOCK_STREAM", NULL);
	OK("socketpair() 2");

	if (fcntl(sv[0], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_STREAM", "O_NONBLOCK");
	OK("fcntl() 3");
	if (fcntl(sv[1], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_STREAM", "O_NONBLOCK");
	OK("fcntl() 4");

	test_evfilt_read(kq, sv, "PF_UNIX, SOCK_STREAM");

	if (close(sv[0]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_STREAM", "sv[0]");
	OK("close() 3");
	if (close(sv[1]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_STREAM", "sv[1]");
	OK("close() 4");

	/*
	 * Create a UNIX domain stream socket, and attach/test/detach a
	 * write filter on it.
	 */
	if (socketpair(PF_UNIX, SOCK_STREAM, 0, sv) == -1)
		fail(errno, "socketpair", "PF_UNIX, SOCK_STREAM", NULL);
	OK("socketpair() 3");

	if (fcntl(sv[0], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_STREAM", "O_NONBLOCK");
	OK("fcntl() 5");
	if (fcntl(sv[1], F_SETFL, O_NONBLOCK) != 0)
		fail(errno, "fcntl", "PF_UNIX, SOCK_STREAM", "O_NONBLOCK");
	OK("fcntl() 6");

	test_evfilt_write(kq, sv, "PF_UNIX, SOCK_STREAM");

	if (close(sv[0]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_STREAM", "sv[0]");
	OK("close() 5");
	if (close(sv[1]) == -1)
		fail(errno, "close", "PF_UNIX/SOCK_STREAM", "sv[1]");
	OK("close() 6");

	if (close(kq) == -1)
		fail(errno, "close", "kq", NULL);
	OK("close() 7");

	return (0);
}