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
typedef  int socklen_t ;
typedef  int /*<<< orphan*/  sin_local ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TCP_PORT ; 
 int /*<<< orphan*/  bzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 scalar_t__ connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  err (int,char*) ; 
 int errno ; 
 scalar_t__ getsockname (int,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tcp_drop (struct sockaddr_in*,struct sockaddr_in*) ; 

__attribute__((used)) static void
tcp_client(pid_t partner, int dropflag)
{
	struct sockaddr_in sin, sin_local;
	int error, sock;
	socklen_t slen;

	sleep(1);

	sock = socket(PF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "socket");
	}

	bzero(&sin, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_len = sizeof(sin);
	sin.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);
	sin.sin_port = htons(TCP_PORT);

	if (connect(sock, (struct sockaddr *)&sin, sizeof(sin)) < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "connect");
	}

	slen = sizeof(sin_local);
	if (getsockname(sock, (struct sockaddr *)&sin_local, &slen) < 0) {
		error = errno;
		(void)kill(partner, SIGKILL);
		errno = error;
		err(-1, "getsockname");
	}

	if (dropflag) {
		if (tcp_drop(&sin_local, &sin) < 0) {
			error = errno;
			(void)kill(partner, SIGKILL);
			errno = error;
			err(-1, "tcp_drop");
		}
		sleep(2);
	}
	close(sock);
}