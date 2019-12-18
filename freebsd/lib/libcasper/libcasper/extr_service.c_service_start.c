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
struct service_connection {int dummy; } ;
struct service {scalar_t__ s_magic; int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_name; } ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 scalar_t__ FD_ISSET (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ FD_SETSIZE ; 
 int /*<<< orphan*/  FD_ZERO (int /*<<< orphan*/ *) ; 
 scalar_t__ SERVICE_MAGIC ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int fd_add (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int select (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  service_clean (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * service_connection_add (struct service*,int,int /*<<< orphan*/ *) ; 
 struct service_connection* service_connection_first (struct service*) ; 
 int /*<<< orphan*/  service_connection_get_sock (struct service_connection*) ; 
 struct service_connection* service_connection_next (struct service_connection*) ; 
 int /*<<< orphan*/  service_message (struct service*,struct service_connection*) ; 
 int /*<<< orphan*/  setproctitle (char*,int /*<<< orphan*/ ) ; 

void
service_start(struct service *service, int sock, int procfd)
{
	struct service_connection *sconn, *sconntmp;
	fd_set fds;
	int maxfd, nfds;

	assert(service != NULL);
	assert(service->s_magic == SERVICE_MAGIC);
	setproctitle("%s", service->s_name);
	service_clean(sock, procfd, service->s_flags);

	if (service_connection_add(service, sock, NULL) == NULL)
		_exit(1);

	for (;;) {
		FD_ZERO(&fds);
		maxfd = -1;
		for (sconn = service_connection_first(service); sconn != NULL;
		    sconn = service_connection_next(sconn)) {
			maxfd = fd_add(&fds, maxfd,
			    service_connection_get_sock(sconn));
		}

		assert(maxfd >= 0);
		assert(maxfd + 1 <= (int)FD_SETSIZE);
		nfds = select(maxfd + 1, &fds, NULL, NULL, NULL);
		if (nfds < 0) {
			if (errno != EINTR)
				_exit(1);
			continue;
		} else if (nfds == 0) {
			/* Timeout. */
			abort();
		}

		for (sconn = service_connection_first(service); sconn != NULL;
		    sconn = sconntmp) {
			/*
			 * Prepare for connection to be removed from the list
			 * on failure.
			 */
			sconntmp = service_connection_next(sconn);
			if (FD_ISSET(service_connection_get_sock(sconn), &fds))
				service_message(service, sconn);
		}
		if (service_connection_first(service) == NULL) {
			/*
			 * No connections left, exiting.
			 */
			break;
		}
	}

	_exit(0);
}