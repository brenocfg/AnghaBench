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
struct sockaddr_in {int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct pollfd {int fd; int events; int revents; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  F_GETFL ; 
 int /*<<< orphan*/  F_SETFL ; 
 int /*<<< orphan*/  INADDR_LOOPBACK ; 
 int O_NONBLOCK ; 
 int POLLOUT ; 
 int /*<<< orphan*/  SIGALRM ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 int accept (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  alarm (int) ; 
 int bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  close (int) ; 
 int connect (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  do_alrm ; 
 int fcntl (int,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (int) ; 
 int listen (int,int) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int write (int,char*,int) ; 

int
main(void)
{
	int o, s, t, u, do_t, do_u;
	struct pollfd pfd[2];
	struct sockaddr_in sa;
	char buf[4096];

	printf("1..1\n");
	signal(SIGALRM, do_alrm);
	alarm(20);

	s = socket(AF_INET, SOCK_STREAM, 0);
	if (s == -1)
		return 1;
	o = 1;
	setsockopt(s, SOL_SOCKET, SO_REUSEADDR, &o, sizeof o);
	memset(&sa, 0, sizeof sa);
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(3737);
	if (bind(s, (struct sockaddr *) &sa, sizeof sa) == -1)
		return 1;
	if (listen(s, 1) == -1)
		return 1;
	t = socket(AF_INET, SOCK_STREAM, 0);
	if (t == -1)
		return 1;
	if (connect(t, (struct sockaddr *) &sa, sizeof sa) == -1)
		return 1;
	u = accept(s, 0, 0);
	if (u == -1)
		return 1;
	close(s);
	fcntl(t, F_SETFL, fcntl(t, F_GETFL) | O_NONBLOCK);
	fcntl(u, F_SETFL, fcntl(t, F_GETFL) | O_NONBLOCK);
	do_t = 1;
	do_u = 1;
	pfd[0].fd = t;
	pfd[0].events = POLLOUT;
	pfd[1].fd = u;
	pfd[1].events = POLLOUT;
	while (do_t || do_u) {
		if (poll(pfd, 2, 1000) == 0) {
			if (do_t) {
				close(t);
				pfd[0].fd = -1;
				do_t = 0;
			}
			continue;
		}
		if (pfd[0].revents & POLLOUT) {
			if (write(t, buf, sizeof buf) == -1) {
				close(t);
				pfd[0].fd = -1;
				do_t = 0;
			}
		}
		if (pfd[1].revents & POLLOUT) {
			if (write(u, buf, sizeof buf) == -1) {
				close(u);
				pfd[1].fd = -1;
				do_u = 0;
			}
		}
	}

	printf("ok 1 - tcpfullwindowrst\n");
	return 0;
}