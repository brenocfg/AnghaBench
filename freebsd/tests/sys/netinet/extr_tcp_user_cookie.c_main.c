#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  srv ;
typedef  int /*<<< orphan*/  cookie ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  EX_OSERR ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_USER_COOKIE ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int atoi (char*) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int buflen ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  htons (int) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int read (int,char**,int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  warn (char*) ; 

int
main(int argc, char **argv)
{
	struct sockaddr_in srv;
	int sock, accepted, port, cookie;
	int ret;
	char recvbuf[buflen];

	if (argc != 3) {
		fprintf(stderr, "Usage: %s port cookie\n", argv[0]);
		exit(2);
	}

	port = atoi(argv[1]);
	cookie = atoi(argv[2]);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0)
		err(EXIT_FAILURE, "socket");

	memset(&srv, 0, sizeof(srv));
	srv.sin_len = sizeof(srv);
	srv.sin_family = AF_INET;
	srv.sin_port = htons(port);
	srv.sin_addr.s_addr = INADDR_ANY;

	if (bind(sock, (struct sockaddr *)&srv, srv.sin_len) < 0)
		err(EX_OSERR, "failed to bind to port %d", port);

	if (listen(sock, 5) < 0)
		err(EX_OSERR, "failed to listen on socket");

	ret = setsockopt(sock, SOL_SOCKET, SO_USER_COOKIE, &cookie, sizeof(cookie));
	if (ret < 0)
		err(EX_OSERR, "setsockopt(SO_USER_COOKIE)");

	while (1) {

		accepted = accept(sock, NULL, 0);

		if (accepted < 0)
			err(EX_OSERR, "accept failed");

		ret = setsockopt(accepted, SOL_SOCKET, SO_USER_COOKIE,
				 &cookie, sizeof(cookie));
		if (ret < 0)
			err(EX_OSERR, "setsockopt(SO_USER_COOKIE)");

		ret = read(accepted, &recvbuf, buflen);

		if (ret < 0)
			warn("failed read");

		close(accepted);
	}

	return (0);
}