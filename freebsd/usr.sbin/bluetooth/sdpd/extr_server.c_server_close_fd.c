#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* server_p ;
typedef  TYPE_2__* provider_p ;
typedef  size_t int32_t ;
struct TYPE_11__ {int /*<<< orphan*/ * rsp; int /*<<< orphan*/  valid; } ;
struct TYPE_10__ {size_t fd; } ;
struct TYPE_9__ {size_t maxfd; TYPE_8__* fdidx; int /*<<< orphan*/  fdset; } ;

/* Variables and functions */
 int /*<<< orphan*/  FD_CLR (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FD_ISSET (size_t,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close (size_t) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (TYPE_8__*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* provider_get_first () ; 
 TYPE_2__* provider_get_next (TYPE_2__*) ; 
 int /*<<< orphan*/  provider_unregister (TYPE_2__*) ; 

__attribute__((used)) static void
server_close_fd(server_p srv, int32_t fd)
{
	provider_p	provider = NULL, provider_next = NULL;

	assert(FD_ISSET(fd, &srv->fdset));
	assert(srv->fdidx[fd].valid);

	close(fd);

	FD_CLR(fd, &srv->fdset);
	if (fd == srv->maxfd)
		srv->maxfd --;

	if (srv->fdidx[fd].rsp != NULL)
		free(srv->fdidx[fd].rsp);

	memset(&srv->fdidx[fd], 0, sizeof(srv->fdidx[fd]));

	for (provider = provider_get_first();
	     provider != NULL;
	     provider = provider_next) {
		provider_next = provider_get_next(provider);

		if (provider->fd == fd)
			provider_unregister(provider);
	}
}