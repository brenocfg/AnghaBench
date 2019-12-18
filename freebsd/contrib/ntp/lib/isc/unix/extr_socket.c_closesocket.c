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
typedef  scalar_t__ isc_sockettype_t ;
struct TYPE_7__ {scalar_t__* fdstate; int maxfd; int* pipe_fds; int /*<<< orphan*/  lock; int /*<<< orphan*/ * fdlock; int /*<<< orphan*/  stats; int /*<<< orphan*/ ** fds; } ;
typedef  TYPE_1__ isc__socketmgr_t ;
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/ * statsindex; } ;
typedef  TYPE_2__ isc__socket_t ;

/* Variables and functions */
 scalar_t__ CLOSED ; 
 scalar_t__ CLOSE_PENDING ; 
 int FDLOCK_ID (int) ; 
 int /*<<< orphan*/  LOCK (int /*<<< orphan*/ *) ; 
 scalar_t__ MANAGED ; 
 int /*<<< orphan*/  SELECT_POKE_CLOSE ; 
 int /*<<< orphan*/  SELECT_POKE_READ ; 
 int /*<<< orphan*/  SELECT_POKE_WRITE ; 
 size_t STATID_CLOSE ; 
 int /*<<< orphan*/  UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_stats (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ isc_sockettype_fdwatch ; 
 int /*<<< orphan*/  select_poke (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unwatch_fd (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
closesocket(isc__socketmgr_t *manager, isc__socket_t *sock, int fd) {
	isc_sockettype_t type = sock->type;
	int lockid = FDLOCK_ID(fd);

	/*
	 * No one has this socket open, so the watcher doesn't have to be
	 * poked, and the socket doesn't have to be locked.
	 */
	LOCK(&manager->fdlock[lockid]);
	manager->fds[fd] = NULL;
	if (type == isc_sockettype_fdwatch)
		manager->fdstate[fd] = CLOSED;
	else
		manager->fdstate[fd] = CLOSE_PENDING;
	UNLOCK(&manager->fdlock[lockid]);
	if (type == isc_sockettype_fdwatch) {
		/*
		 * The caller may close the socket once this function returns,
		 * and `fd' may be reassigned for a new socket.  So we do
		 * unwatch_fd() here, rather than defer it via select_poke().
		 * Note: this may complicate data protection among threads and
		 * may reduce performance due to additional locks.  One way to
		 * solve this would be to dup() the watched descriptor, but we
		 * take a simpler approach at this moment.
		 */
		(void)unwatch_fd(manager, fd, SELECT_POKE_READ);
		(void)unwatch_fd(manager, fd, SELECT_POKE_WRITE);
	} else
		select_poke(manager, fd, SELECT_POKE_CLOSE);

	inc_stats(manager->stats, sock->statsindex[STATID_CLOSE]);

	/*
	 * update manager->maxfd here (XXX: this should be implemented more
	 * efficiently)
	 */
#ifdef USE_SELECT
	LOCK(&manager->lock);
	if (manager->maxfd == fd) {
		int i;

		manager->maxfd = 0;
		for (i = fd - 1; i >= 0; i--) {
			lockid = FDLOCK_ID(i);

			LOCK(&manager->fdlock[lockid]);
			if (manager->fdstate[i] == MANAGED) {
				manager->maxfd = i;
				UNLOCK(&manager->fdlock[lockid]);
				break;
			}
			UNLOCK(&manager->fdlock[lockid]);
		}
#ifdef ISC_PLATFORM_USETHREADS
		if (manager->maxfd < manager->pipe_fds[0])
			manager->maxfd = manager->pipe_fds[0];
#endif
	}
	UNLOCK(&manager->lock);
#endif	/* USE_SELECT */
}