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
typedef  int /*<<< orphan*/  val ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  ATF_REQUIRE (int) ; 
 int BUFSIZE ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_UNSPEC ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int /*<<< orphan*/  atf_tc_fail (char*) ; 
 scalar_t__ close (int) ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (char*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,void*,int) ; 
 int /*<<< orphan*/  memset (void*,char,int) ; 
 int page ; 
 int read (int,char*,int) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int write (int,char*,int) ; 

void
testloan(void *vp, void *vp2, char pat, int docheck)
{
	char buf[BUFSIZE];
	char backup[BUFSIZE];
	ssize_t nwritten;
	ssize_t nread;
	int fds[2];
	int val;

	val = BUFSIZE;

	if (docheck != 0)
		(void)memcpy(backup, vp, BUFSIZE);

	if (socketpair(AF_LOCAL, SOCK_STREAM, PF_UNSPEC, fds) != 0)
		atf_tc_fail("socketpair() failed");

	val = BUFSIZE;

	if (setsockopt(fds[1], SOL_SOCKET, SO_RCVBUF, &val, sizeof(val)) != 0)
		atf_tc_fail("setsockopt() failed, SO_RCVBUF");

	val = BUFSIZE;

	if (setsockopt(fds[0], SOL_SOCKET, SO_SNDBUF, &val, sizeof(val)) != 0)
		atf_tc_fail("setsockopt() failed, SO_SNDBUF");

	if (fcntl(fds[0], F_SETFL, O_NONBLOCK) != 0)
		atf_tc_fail("fcntl() failed");

	nwritten = write(fds[0], (char *)vp + page, BUFSIZE - page);

	if (nwritten == -1)
		atf_tc_fail("write() failed");

	/* Break loan. */
	(void)memset(vp2, pat, BUFSIZE);

	nread = read(fds[1], buf + page, BUFSIZE - page);

	if (nread == -1)
		atf_tc_fail("read() failed");

	if (nread != nwritten)
		atf_tc_fail("too short read");

	if (docheck != 0 && memcmp(backup, buf + page, nread) != 0)
		atf_tc_fail("data mismatch");

	ATF_REQUIRE(close(fds[0]) == 0);
	ATF_REQUIRE(close(fds[1]) == 0);
}