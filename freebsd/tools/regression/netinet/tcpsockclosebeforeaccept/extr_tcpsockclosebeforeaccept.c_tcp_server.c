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
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_PORT ; 
 int accept (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ listen (int,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_server(pid_t partner)
{
	int error, listen_fd, accept_fd;
	struct sockaddr_in sin;

	listen_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (listen_fd < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "tcp_server: socket");
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sin.sin_port = htons(TCP_PORT);

	if (bind(listen_fd, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "tcp_server: bind");
	}

	if (listen(listen_fd, -1) < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "tcp_server: listen");
	}

	sleep(10);

	accept_fd = accept(listen_fd, NULL, NULL);
	if (accept_fd < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "tcp_server: accept");
	}
	close(accept_fd);
	close(listen_fd);
}