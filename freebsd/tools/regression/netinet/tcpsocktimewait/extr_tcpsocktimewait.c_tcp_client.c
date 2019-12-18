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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int sin_len; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SHUT_RDWR ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 scalar_t__ shutdown (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
tcp_client(pid_t partner, u_short port, int secs)
{
	struct sockaddr_in sin;
	int error, sock;

	sleep(1);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		error = errno;
		(void)kill(partner, SIGTERM);
		errno = error;
		err(-1, "socket");
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
	sin.sin_port = port;

	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		error = errno;
		(void)kill(partner, SIGTERM);
		errno = error;
		err(-1, "connect");
	}

	if (shutdown(sock, SHUT_RDWR) < 0) {
		error = errno;
		(void)kill(partner, SIGTERM);
		errno = error;
		err(-1, "shutdown");
	}

	sleep(secs);
	close(sock);
}