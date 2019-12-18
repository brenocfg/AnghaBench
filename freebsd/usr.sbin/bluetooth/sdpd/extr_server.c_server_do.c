#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* server_p ;
typedef  scalar_t__ int32_t ;
typedef  int /*<<< orphan*/  fdset ;
typedef  int /*<<< orphan*/  fd_set ;
struct TYPE_8__ {scalar_t__ maxfd; TYPE_1__* fdidx; int /*<<< orphan*/  fdset; } ;
struct TYPE_7__ {scalar_t__ server; int /*<<< orphan*/  valid; } ;

/* Variables and functions */
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  FD_ISSET (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  log_err (char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ select (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  server_accept_client (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  server_close_fd (TYPE_2__*,scalar_t__) ; 
 scalar_t__ server_process_request (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 

int32_t
server_do(server_p srv)
{
	fd_set	fdset;
	int32_t	n, fd;

	assert(srv != NULL);

	/* Copy cached version of the fd set and call select */
	memcpy(&fdset, &srv->fdset, sizeof(fdset));
	n = select(srv->maxfd + 1, &fdset, NULL, NULL, NULL);
	if (n < 0) {
		if (errno == EINTR)
			return (0);

		log_err("Could not select(%d, %p). %s (%d)",
			srv->maxfd + 1, &fdset, strerror(errno), errno);

		return (-1);
	}

	/* Process  descriptors */
	for (fd = 0; fd < srv->maxfd + 1 && n > 0; fd ++) {
		if (!FD_ISSET(fd, &fdset))
			continue;

		assert(srv->fdidx[fd].valid);
		n --;

		if (srv->fdidx[fd].server)
			server_accept_client(srv, fd);
		else if (server_process_request(srv, fd) != 0)
			server_close_fd(srv, fd);
	}

	return (0);
	
}