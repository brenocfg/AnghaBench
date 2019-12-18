#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* server_p ;
struct TYPE_7__ {scalar_t__ valid; } ;
struct TYPE_6__ {int maxfd; TYPE_5__* fdidx; TYPE_5__* req; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  server_close_fd (TYPE_1__*,int) ; 

void
server_shutdown(server_p srv)
{
	int	fd;

	assert(srv != NULL);

	for (fd = 0; fd < srv->maxfd + 1; fd ++)
		if (srv->fdidx[fd].valid)
			server_close_fd(srv, fd);

	free(srv->req);
	free(srv->fdidx);

	memset(srv, 0, sizeof(*srv));
}