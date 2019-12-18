#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int* pipe_fds; scalar_t__ maxsocks; } ;
typedef  TYPE_1__ isc__socketmgr_t ;
typedef  int /*<<< orphan*/  fd_set ;

/* Variables and functions */
 int /*<<< orphan*/  FD_ISSET (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  REQUIRE (int) ; 
 int /*<<< orphan*/  process_fd (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_fds(isc__socketmgr_t *manager, int maxfd, fd_set *readfds,
	    fd_set *writefds)
{
	int i;

	REQUIRE(maxfd <= (int)manager->maxsocks);

	for (i = 0; i < maxfd; i++) {
#ifdef USE_WATCHER_THREAD
		if (i == manager->pipe_fds[0] || i == manager->pipe_fds[1])
			continue;
#endif /* USE_WATCHER_THREAD */
		process_fd(manager, i, FD_ISSET(i, readfds),
			   FD_ISSET(i, writefds));
	}
}