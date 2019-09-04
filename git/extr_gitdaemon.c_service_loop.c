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
struct socketlist {int nr; int /*<<< orphan*/ * list; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct pollfd {int events; int revents; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  ss ;
typedef  int socklen_t ;

/* Variables and functions */
#define  EAGAIN 130 
#define  ECONNABORTED 129 
#define  EINTR 128 
 int POLLIN ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int accept (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int /*<<< orphan*/  check_dead_children () ; 
 int /*<<< orphan*/  child_handler ; 
 int /*<<< orphan*/  die_errno (char*) ; 
 int errno ; 
 int /*<<< orphan*/  handle (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  logerror (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  signal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  strerror (int) ; 
 struct pollfd* xcalloc (int,int) ; 

__attribute__((used)) static int service_loop(struct socketlist *socklist)
{
	struct pollfd *pfd;
	int i;

	pfd = xcalloc(socklist->nr, sizeof(struct pollfd));

	for (i = 0; i < socklist->nr; i++) {
		pfd[i].fd = socklist->list[i];
		pfd[i].events = POLLIN;
	}

	signal(SIGCHLD, child_handler);

	for (;;) {
		int i;

		check_dead_children();

		if (poll(pfd, socklist->nr, -1) < 0) {
			if (errno != EINTR) {
				logerror("Poll failed, resuming: %s",
				      strerror(errno));
				sleep(1);
			}
			continue;
		}

		for (i = 0; i < socklist->nr; i++) {
			if (pfd[i].revents & POLLIN) {
				union {
					struct sockaddr sa;
					struct sockaddr_in sai;
#ifndef NO_IPV6
					struct sockaddr_in6 sai6;
#endif
				} ss;
				socklen_t sslen = sizeof(ss);
				int incoming = accept(pfd[i].fd, &ss.sa, &sslen);
				if (incoming < 0) {
					switch (errno) {
					case EAGAIN:
					case EINTR:
					case ECONNABORTED:
						continue;
					default:
						die_errno("accept returned");
					}
				}
				handle(incoming, &ss.sa, sslen);
			}
		}
	}
}