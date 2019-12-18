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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  md5enable ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 scalar_t__ EINPROGRESS ; 
 scalar_t__ ENOPROTOOPT ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  O_NONBLOCK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_MD5SIG ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 scalar_t__ errno ; 
 scalar_t__ fcntl (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (long) ; 
 scalar_t__ inet_aton (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char*) ; 
 long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static void
tcpconnect_client(int argc, char *argv[])
{
	struct sockaddr_in sin;
	long count, i, port;
	char *dummy;
	int sock;
	int nonblock = 0, md5enable = 0;

	if (argc < 3 || argc > 5)
		usage();
	for (i=3; i < argc; i++) {
		if (strcmp(argv[i], "nonblock") == 0)
			nonblock = 1;
		if (strcmp(argv[i], "tcpmd5") == 0)
			md5enable = 1;
	}

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	if (inet_aton(argv[0], &sin.sin_addr) == 0)
		err(-1, "listen");

	port = strtoul(argv[1], &dummy, 10);
	if (port < 1 || port > 65535 || *dummy != '\0')
		usage();
	sin.sin_port = htons(port);

	count = strtoul(argv[2], &dummy, 10);
	if (count < 1 || count > 100000 || *dummy != '\0')
		usage();

	for (i = 0; i < count; i++) {
		sock = socket(PF_INET, SOCK_STREAM, 0);
		if (sock == -1)
			err(-1, "socket");

		/* No warning in default case on ENOPROTOOPT. */
		if (setsockopt(sock, IPPROTO_TCP, TCP_MD5SIG,
		    &md5enable, sizeof(md5enable)) != 0) {
			if (errno == ENOPROTOOPT && md5enable > 0)
				err(-1, "setsockopt(TCP_MD5SIG)");
			else if (errno != ENOPROTOOPT)
				warn("setsockopt(TCP_MD5SIG)");
		}

		if (nonblock) {
			if (fcntl(sock, F_SETFL, O_NONBLOCK) != 0)
				err(-1, "fcntl(F_SETFL)");

			if (connect(sock, (struct sockaddr *)&sin,
			    sizeof(sin)) == -1 && errno != EINPROGRESS)
				err(-1, "connect");
		} else {
			if (connect(sock, (struct sockaddr *)&sin,
			    sizeof(sin)) == -1)
				err(-1, "connect");
		}

		close(sock);
	}
}