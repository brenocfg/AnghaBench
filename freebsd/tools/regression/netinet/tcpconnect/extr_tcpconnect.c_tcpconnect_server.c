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
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (long) ; 
 int listen (int,int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long strtoul (char*,char**,int) ; 
 int /*<<< orphan*/  usage () ; 

__attribute__((used)) static void
tcpconnect_server(int argc, char *argv[])
{
	int listen_sock, accept_sock;
	struct sockaddr_in sin;
	char *dummy;
	long port;

	if (argc != 1)
		usage();

	bzero(&sin, sizeof(sin));
	sin.sin_len = sizeof(sin);
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	port = strtoul(argv[0], &dummy, 10);
	if (port < 1 || port > 65535 || *dummy != '\0')
		usage();
	sin.sin_port = htons(port);

	listen_sock = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_sock == -1)
		err(-1, "socket");

	if (bind(listen_sock, (struct sockaddr *)&sin, sizeof(sin)) == -1)
		err(-1, "bind");

	if (listen(listen_sock, -1) == -1)
		err(-1, "listen");

	while (1) {
		accept_sock = accept(listen_sock, NULL, NULL);
		close(accept_sock);
	}
}