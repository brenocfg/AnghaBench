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
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stderr ; 
 long strtol (char*,char**,int) ; 
 int /*<<< orphan*/  tcp_pair (long,int*) ; 
 int /*<<< orphan*/  tcp_setup (long) ; 
 int /*<<< orphan*/  tcp_teardown () ; 
 int /*<<< orphan*/  test_send_dontsignal (char*,int,int) ; 
 int /*<<< orphan*/  test_send_wantsignal (char*,int,int) ; 
 int /*<<< orphan*/  test_write_dontsignal (char*,int,int) ; 
 int /*<<< orphan*/  test_write_wantsignal (char*,int,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warnx (char*) ; 

int
main(int argc, char *argv[])
{
	char *dummy;
	int sock[2];
	long port;

	if (argc != 2)
		usage();

	port = strtol(argv[1], &dummy, 10);
	if (port < 0 || port > 65535 || *dummy != '\0')
		usage();

#ifndef SO_NOSIGPIPE
	warnx("sigpipe: SO_NOSIGPIPE not defined, skipping some tests");
#endif

	/*
	 * UNIX domain socketpair().
	 */
	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sock) < 0)
		err(-1, "socketpair(PF_LOCAL, SOCK_STREAM)");
	test_send_wantsignal("test_send_wantsignal(PF_LOCAL)", sock[0],
	    sock[1]);

#ifdef SO_NOSIGPIPE
	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sock) < 0)
		err(-1, "socketpair(PF_LOCAL, SOCK_STREAM)");
	test_send_dontsignal("test_send_dontsignal(PF_LOCAL)", sock[0],
	    sock[1]);
#endif

	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sock) < 0)
		err(-1, "socketpair(PF_LOCAL, SOCK_STREAM)");
	test_write_wantsignal("test_write_wantsignal(PF_LOCAL)", sock[0],
	    sock[1]);

#ifdef SO_NOSIGPIPE
	if (socketpair(PF_LOCAL, SOCK_STREAM, 0, sock) < 0)
		err(-1, "socketpair(PF_LOCAL, SOCK_STREAM)");
	test_write_dontsignal("test_write_dontsignal(PF_LOCAL)", sock[0],
	    sock[1]);
#endif

	/*
	 * TCP.
	 */
	tcp_setup(port);
	tcp_pair(port, sock);
	test_send_wantsignal("test_send_wantsignal(PF_INET)", sock[0],
	    sock[1]);

#ifdef SO_NOSIGPIPE
	tcp_pair(port, sock);
	test_send_dontsignal("test_send_dontsignal(PF_INET)", sock[0],
	    sock[1]);
#endif

	tcp_pair(port, sock);
	test_write_wantsignal("test_write_wantsignal(PF_INET)", sock[0],
	    sock[1]);

#ifdef SO_NOSIGPIPE
	tcp_pair(port, sock);
	test_write_dontsignal("test_write_dontsignal(PF_INET)", sock[0],
	    sock[1]);
#endif
	tcp_teardown();

	fprintf(stderr, "PASS\n");
	return (0);
}