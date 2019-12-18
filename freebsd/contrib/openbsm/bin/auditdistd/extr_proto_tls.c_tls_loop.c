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
typedef  int /*<<< orphan*/  fd_set ;
typedef  int /*<<< orphan*/  SSL ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  EX_TEMPFAIL ; 
 scalar_t__ FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_SET (int,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 int MAX (int,int) ; 
 int /*<<< orphan*/  PJDLOG_ASSERT (int) ; 
 int SSL_get_fd (int /*<<< orphan*/ *) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pjdlog_exit (int /*<<< orphan*/ ,char*) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ssl_recv_tcp_send (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  tcp_recv_ssl_send (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
tls_loop(int sockfd, SSL *tcpssl)
{
	fd_set fds;
	int maxfd, tcpfd;

	tcpfd = SSL_get_fd(tcpssl);
	PJDLOG_ASSERT(tcpfd >= 0);

	for (;;) {
		FD_ZERO(&fds);
		FD_SET(sockfd, &fds);
		FD_SET(tcpfd, &fds);
		maxfd = MAX(sockfd, tcpfd);

		PJDLOG_ASSERT(maxfd + 1 <= (int)FD_SETSIZE);
		if (select(maxfd + 1, &fds, NULL, NULL, NULL) == -1) {
			if (errno == EINTR)
				continue;
			pjdlog_exit(EX_TEMPFAIL, "select() failed");
		}
		if (FD_ISSET(sockfd, &fds))
			tcp_recv_ssl_send(sockfd, tcpssl);
		if (FD_ISSET(tcpfd, &fds))
			ssl_recv_tcp_send(tcpssl, sockfd);
	}
}