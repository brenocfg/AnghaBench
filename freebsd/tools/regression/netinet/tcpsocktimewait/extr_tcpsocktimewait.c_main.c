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
typedef  int /*<<< orphan*/  u_short ;
struct TYPE_2__ {void* s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; void* sin_family; TYPE_1__ sin_addr; } ;
struct sockaddr {int dummy; } ;
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 void* AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGTERM ; 
 scalar_t__ SIG_ERR ; 
 int /*<<< orphan*/  SIG_IGN ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 scalar_t__ fork () ; 
 scalar_t__ getpid () ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 void* htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int ntohs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 scalar_t__ signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tcp_client (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tcp_server (scalar_t__,int) ; 

int
main(int argc, char *argv[])
{
	struct sockaddr_in sin;
	pid_t child_pid, parent_pid;
	int listen_fd;
	socklen_t len;
	u_short port;

	if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
		err(-1, "signal");

	/*
	 * Run the whole thing twice: once, with a short sleep in the client,
	 * so that we close before time wait runs out, and once with a long
	 * sleep so that the time wait terminates while the socket is open.
	 * We don't reuse listen sockets between runs.
	 */
	listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		err(-1, "socket");

	/*
	 * We use the loopback, but let the kernel select a port for the
	 * server socket.
	 */
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (bind(listen_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(-1, "bind");

	if (listen(listen_fd, -1) < 0)
		err(-1, "listen");

	/*
	 * Query the port so that the client can use it.
	 */
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	len = sizeof(sin);
	if (getsockname(listen_fd, (struct sockaddr *)&sin, &len) < 0)
		err(-1, "getsockname");
	port = sin.sin_port;
	printf("Using port %d\n", ntohs(port));

	parent_pid = getpid();
	child_pid = fork();
	if (child_pid < 0)
		err(-1, "fork");
	if (child_pid == 0) {
		child_pid = getpid();
		tcp_server(child_pid, listen_fd);
		exit(0);
	} else
		tcp_client(parent_pid, port, 1);
	(void)kill(child_pid, SIGTERM);
	close(listen_fd);
	sleep(5);

	/*
	 * Start again, this time long sleep.
	 */
	listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0)
		err(-1, "socket");

	/*
	 * We use the loopback, but let the kernel select a port for the
	 * server socket.
	 */
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	if (bind(listen_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0)
		err(-1, "bind");

	if (listen(listen_fd, -1) < 0)
		err(-1, "listen");

	/*
	 * Query the port so that the client can use it.
	 */
	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	len = sizeof(sin);
	if (getsockname(listen_fd, (struct sockaddr *)&sin, &len) < 0)
		err(-1, "getsockname");
	port = sin.sin_port;
	printf("Using port %d\n", ntohs(port));

	parent_pid = getpid();
	child_pid = fork();
	if (child_pid < 0)
		err(-1, "fork");
	if (child_pid == 0) {
		child_pid = getpid();
		tcp_server(parent_pid, listen_fd);
	} else
		tcp_client(child_pid, port, 800);

	return (0);
}